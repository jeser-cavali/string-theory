#include "file_handler.hpp"

#include <filesystem>

std::unordered_map<enum argument_type, std::string> map_arguments(int argc, char* argv[]){

    if(argc == 1){
        throw std::runtime_error("Missing arguments");
    }

    std::unordered_map<enum argument_type, std::string> new_map;

    int last_item = argc-1;
    bool has_url = false;

    if(argc == 2){
        new_map.insert({COMMAND, argv[1]});
    } else if(argc == 3){
        new_map.insert({COMMAND, argv[1]});
        new_map.insert({URL, argv[2]});
        has_url = true;
    } else{
        new_map.insert({COMMAND, argv[1]});
        for(int i = 2; i < (last_item-1); i++){
            new_map.insert({MODIFIER, argv[i]});
        }
        new_map.insert({URL, argv[last_item]});
        has_url = true;
    }

    if(has_url){
        std::filesystem::path url = new_map[URL];

        if(std::filesystem::exists(url)){
            if(std::filesystem::is_regular_file(url)){
                new_map.insert({MUSIC, new_map[URL]});
                new_map.erase(URL);
            } else if(std::filesystem::is_directory(url)){
                new_map.insert({DIRECTORY, new_map[URL]});
                new_map.erase(URL);
            }
        } else{
            throw std::runtime_error("Provided filepath does not exist");
        }
    }

    return new_map;
}