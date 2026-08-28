#include "inputHandler.hpp"

#include <unordered_map>
#include <array>
#include <algorithm>
#include <iostream>

bool isCommand(std::string string){
    return std::ranges::any_of(command_list::commands, [string](std::string_view s) {
        return s == string;
    });
}

bool isModifier(std::string string){
    return std::ranges::any_of(modifier_list::modifiers, [string](std::string_view s) {
        return s == string;
    });
}

std::string urltypeToString(URL_TYPES url_type){
    std::array<std::string, 2> ref = {
        "file",
        "directory"
    };
    return ref.at(url_type);
}

inputStructure::inputStructure(int argc, char* argv[]){
    if(argc <= 1){
        throw std::runtime_error("NO ARGUMENTS PROVIDED");
    }

    for(int i = 1; i < argc; i++){
        if(isCommand(argv[i])){
            command = argv[i];
        }

        if(isModifier(argv[i])){
            modifiers.emplace(argv[i]);
        }

        if(std::filesystem::exists(argv[i])){
            url = std::filesystem::path(argv[i]);
            if(std::filesystem::is_regular_file(argv[i])){
                urlType = URL_TYPES::MUSIC;
            } else if(std::filesystem::is_directory(argv[i])){
                urlType = URL_TYPES::DIRECTORY;
            }
        }
    }
}

void inputStructure::print(){
    if(command.has_value()) std::cout << "[COMMAND] " << command.value() << std::endl;

    if(!modifiers.empty()){
        for(auto mod : modifiers._Get_container()){
            std::cout << "[MOD] " << mod << std::endl;
        }
    }

    if(url.has_value()) std::cout << "[URL] " << url.value() << std::endl;
    if(urlType.has_value()) std::cout << "[URL_TYPE]" << urltypeToString(urlType.value()) << std::endl;
}