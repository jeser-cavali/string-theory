#include "input_parser.hpp"

#include <filesystem>

bool is_command(std::string string){
    return (
        string == commands::play ||
        string == commands::skip ||
        string == commands::pause ||
        string == commands::back
    );
}

bool is_modifier(std::string string){
    return (
        string == modifiers::rand ||
        string == modifiers::loop
    );
}

bool is_valid_filetype(std::string string){
    return (
        string.contains(valid_filetypes::mp3) ||
        string.contains(valid_filetypes::wav) ||
        string.contains(valid_filetypes::flac) ||
        string.contains(valid_filetypes::ogg)
    );
}

InputStructure::InputStructure(int argc, char* argv[]){
    if(argc == 1){
        throw std::runtime_error("Missing arguments");
    }

    for(int i = 1; i < argc; i++){
        if(is_command(argv[i]) && !command.has_value()){
            command = argv[i];
        } else if(is_modifier(argv[i])){
            if(!command_modifiers.has_value()){
                command_modifiers = {argv[i]};
            } else{
                command_modifiers.value().insert(argv[i]);
            }
        } else if(std::filesystem::exists(argv[i]) && !url.has_value()){
            if(std::filesystem::is_directory(argv[i])){
                url = {DIRECTORY, argv[i]};
            } else if(std::filesystem::is_regular_file(argv[i])){
                if(is_valid_filetype(argv[i])){
                    url = {MUSIC, argv[i]};
                } else{
                    throw std::runtime_error("Invalid filetype");
                }
            } else{
                throw std::runtime_error("Invalid url");
            }
        }
    }

    if(!command.has_value() && url.has_value()){
        command = commands::play;
    }
}

std::optional<std::string> InputStructure::get_command(){
    return command;
}
std::optional<std::unordered_set<std::string>> InputStructure::get_modifiers(){
    return command_modifiers;
}
std::optional<std::pair<argument_type, std::string>> InputStructure::get_url(){
    return url;
}

void InputStructure::print(){
    if(command.has_value()){
        std::cout << "[COMMAND] " << command.value() << std::endl;
    }

    if(command_modifiers.has_value()){
        for(auto entry : command_modifiers.value()){
            std::cout << "[MOD] " << entry << std::endl;
        }
    }

    if(url.has_value()){
        std::cout << "[URL TYPE] " << translate_argument_type(url.value().first) << std::endl;
        std::cout << "[URL] " << url.value().second << std::endl;
    }
}

std::unordered_multimap<enum argument_type, std::string> map_arguments(int argc, char* argv[]){

    if(argc == 1){
        throw std::runtime_error("Missing arguments");
    }

    std::unordered_multimap<enum argument_type, std::string> classified_map;
    bool has_url = false;

    for(int i = 1; i < argc; i++){
        if(is_command(argv[i])){
            classified_map.insert({COMMAND, argv[i]});
        } else if(is_modifier(argv[i])){
            classified_map.insert({MODIFIER, argv[i]});
        } else if(std::filesystem::exists(argv[i])){
            classified_map.insert({URL, argv[i]});
            has_url = true;
        }
    }

    if(has_url){
        std::string url_string = classified_map.find(URL)->second;
        std::filesystem::path url = url_string;

        if(std::filesystem::is_regular_file(url)){
            if(is_valid_filetype(url_string)){
                classified_map.insert({MUSIC, classified_map.find(URL)->second});
                classified_map.erase(URL);
            } else{
                throw std::runtime_error("Invalid filetype");
            }
        } else{
            classified_map.insert({DIRECTORY, classified_map.find(URL)->second});

            for(const auto& entry : std::filesystem::directory_iterator(classified_map.find(DIRECTORY)->second)){
                if(is_valid_filetype(entry.path().string())){
                    classified_map.insert({MUSIC, entry.path().string()});
                }
            }

            if(classified_map.find(MUSIC) == classified_map.end()){
                throw std::runtime_error("Directory has no valid files");
            }

            classified_map.erase(URL);
        }
    }

    return classified_map;
}