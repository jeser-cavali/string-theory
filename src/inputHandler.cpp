#include "inputHandler.hpp"

#include <unordered_map>
#include <array>
#include <algorithm>

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