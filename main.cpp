#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>

enum argument_type{
    COMMAND,
    MODIFIER,
    URL,
    MUSIC,
    DIRECTORY
};

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

int main(int argc, char* argv[]){

    std::unordered_map<enum argument_type, std::string> argument_map;

    try{
        argument_map = map_arguments(argc, argv);
    } catch(const std::runtime_error& e){
        std::cout << "\033[31m" << "ERROR: " << e.what() << "\033[0m" << std::endl;
    }

    /*
    TODO(make custom enum? for console colors);

    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    */

    return 0;
}