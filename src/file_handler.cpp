#include "file_handler.hpp"

#include <filesystem>

namespace valid_filetypes {
    constexpr std::string_view mp3 = ".mp3";
    constexpr std::string_view wav = ".wav";
    constexpr std::string_view flac = ".flac";
    constexpr std::string_view ogg = ".ogg";
}

bool check_mp3(std::string string){
    return string.contains(valid_filetypes::mp3);
}

bool check_wav(std::string string){
    return string.contains(valid_filetypes::wav);
}

bool check_flac(std::string string){
    return string.contains(valid_filetypes::flac);
}

bool check_ogg(std::string string){
    return string.contains(valid_filetypes::ogg);
}

bool check_valid_filetype(std::string string){
    if(
        check_mp3(string) ||
        check_wav(string) ||
        check_flac(string) ||
        check_ogg(string)
    ){
        return true;
    }

    return false;
}

std::unordered_multimap<enum argument_type, std::string> map_arguments(int argc, char* argv[]){

    if(argc == 1){
        throw std::runtime_error("Missing arguments");
    }

    std::unordered_multimap<enum argument_type, std::string> new_map;

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
        std::filesystem::path url = new_map.find(URL)->second;

        if(std::filesystem::exists(url)){
            if(std::filesystem::is_regular_file(url)){
                new_map.insert({MUSIC, new_map.find(URL)->second});
                new_map.erase(URL);
            } else if(std::filesystem::is_directory(url)){
                new_map.insert({DIRECTORY, new_map.find(URL)->second});
                new_map.erase(URL);
            }
        } else{
            throw std::runtime_error("Provided filepath does not exist");
        }
    }

    if(new_map.find(MUSIC) != new_map.end()){
        if(check_valid_filetype(new_map.find(MUSIC)->second) == false){
            throw std::runtime_error("Invalid filetype");
        }
    }

    if(new_map.find(DIRECTORY) != new_map.end()){
        std::vector<std::string> files;

        for(const auto& entry : std::filesystem::directory_iterator(new_map.find(DIRECTORY)->second)){
            if(std::filesystem::is_regular_file(entry.status())){
                if(check_valid_filetype(entry.path().string())){
                    files.push_back(entry.path().string());
                }
            }
        }

        if(files.empty()){
            throw std::runtime_error("Directory has no valid files");
        }

        for(std::string file : files){
            new_map.insert({MUSIC, file});
        }
    }

    return new_map;
}