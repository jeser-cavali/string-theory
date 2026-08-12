#include "file_handler.hpp"

#include <filesystem>

namespace commands {
    constexpr std::string_view implicit_play = ".";
    constexpr std::string_view play = "play";
    constexpr std::string_view skip = "skip";
    constexpr std::string_view pause = "pause";
}

namespace modifiers {
    constexpr std::string_view rand = "rand";
}

namespace valid_filetypes {
    constexpr std::string_view mp3 = ".mp3";
    constexpr std::string_view wav = ".wav";
    constexpr std::string_view flac = ".flac";
    constexpr std::string_view ogg = ".ogg";
}

bool is_command(std::string string){
    return (
        string == commands::implicit_play ||
        string == commands::play ||
        string == commands::skip ||
        string == commands::pause
    );
}

bool is_modifier(std::string string){
    return string == modifiers::rand;
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
    std::unordered_multimap<enum argument_type, std::string> classified_map;

    for(int i = 1; i < argc; i++){
        new_map.insert({UNCLASSIFIED, argv[i]});
    }

    bool has_url = false;

    for(const auto& [key, value] : new_map){
        if(is_command(value)){
            classified_map.insert({COMMAND, value});
        } else if(is_modifier(value)){
            classified_map.insert({MODIFIER, value});
        } else if(std::filesystem::exists(value)){
            classified_map.insert({URL, value});
            has_url = true;
        }
    }

    if(has_url){
        std::filesystem::path url = classified_map.find(URL)->second;

        if(std::filesystem::exists(url)){
            if(std::filesystem::is_regular_file(url)){
                classified_map.insert({MUSIC, classified_map.find(URL)->second});
                classified_map.erase(URL);
            } else if(std::filesystem::is_directory(url)){
                classified_map.insert({DIRECTORY, classified_map.find(URL)->second});
                classified_map.erase(URL);
            }
        } else{
            throw std::runtime_error("Provided filepath does not exist");
        }
    }

    if(classified_map.find(MUSIC) != classified_map.end()){
        if(check_valid_filetype(classified_map.find(MUSIC)->second) == false){
            throw std::runtime_error("Invalid filetype");
        }
    }

    if(classified_map.find(DIRECTORY) != classified_map.end()){
        std::vector<std::string> files;

        for(const auto& entry : std::filesystem::directory_iterator(classified_map.find(DIRECTORY)->second)){
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
            classified_map.insert({MUSIC, file});
        }
    }

    return classified_map;
}