#pragma once

#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <optional>

enum argument_type{
    UNCLASSIFIED,
    COMMAND,
    MODIFIER,
    URL,
    MUSIC,
    DIRECTORY
};

namespace commands {
    constexpr std::string_view play = "play";
    constexpr std::string_view skip = "skip";
    constexpr std::string_view pause = "pause";
    constexpr std::string_view back = "back";
};

namespace modifiers {
    constexpr std::string_view rand = "rand";
    constexpr std::string_view loop = "loop";
};

namespace valid_filetypes {
    constexpr std::string_view mp3 = ".mp3";
    constexpr std::string_view wav = ".wav";
    constexpr std::string_view flac = ".flac";
    constexpr std::string_view ogg = ".ogg";
};

class InputStructure{
    private:
        std::optional<std::string> command;
        std::optional<std::unordered_set<std::string>> command_modifiers;
        std::optional<std::pair<argument_type, std::string>> url;
    public:
        InputStructure(int argc, char* argv[]);
        std::optional<std::string> get_command();
        std::optional<std::unordered_set<std::string>> get_modifiers();
        std::optional<std::pair<argument_type, std::string>> get_url();
        void print();
};

inline std::string translate_argument_type(argument_type enum_item){
    std::string values[6] = {
        "UNCLASSIFIED",
        "COMMAND",
        "MODIFIER",
        "URL",
        "MUSIC",
        "DIRECTORY"
    };
    return values[enum_item];
};

inline enum argument_type reverse_translate_argument_type(std::string string){
    std::unordered_map<std::string, argument_type> values = {
        {"UNCLASSIFIED", UNCLASSIFIED},
        {"COMMAND", COMMAND},
        {"MODIFIER", MODIFIER},
        {"URL", URL},
        {"MUSIC", MUSIC},
        {"DIRECTORY", DIRECTORY}
    };

    if(values.contains(string)){
        return values.at(string);
    } else{
        throw std::runtime_error("String is not <argument_type>");
    }
};

bool is_valid_filetype(std::string string);

std::unordered_multimap<enum argument_type, std::string> map_arguments(int argc, char* argv[]);