#include "input_parser.hpp"

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

bool is_valid_filetype(std::string string){
    return (
        string.contains(valid_filetypes::mp3) ||
        string.contains(valid_filetypes::wav) ||
        string.contains(valid_filetypes::flac) ||
        string.contains(valid_filetypes::ogg)
    );
}

std::unordered_multimap<enum argument_type, std::string> map_arguments(int argc, char* argv[]){

    if(argc == 1){
        throw std::runtime_error("Missing arguments");
    }

    std::unordered_multimap<enum argument_type, std::string> classified_map;
    bool has_url = false;

    for(int i = 1; i < argc; i++){
        if(is_command(argv[i])){
            if(argv[i] == commands::implicit_play){
                classified_map.insert({URL, argv[i]});
                has_url = true;
            } else{
                classified_map.insert({COMMAND, argv[i]});
            }
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