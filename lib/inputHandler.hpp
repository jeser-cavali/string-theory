#pragma once

#include <filesystem>
#include <optional>
#include <queue>
#include <array>

namespace command_list{
    constexpr std::array<std::string_view, 4> commands = {
        "play",
        "pause",
        "skip",
        "stop"
    };
};

namespace modifier_list{
    constexpr std::array<std::string_view, 2> modifiers = {
        "loop",
        "rand"
    };
}

/*
enum COMMANDS{
    PLAY,
    PAUSE,
    SKIP,
    STOP
};

enum MODIFIERS{
    LOOP,
    RAND
};
*/

enum URL_TYPES{
    MUSIC,
    DIRECTORY
};

std::string urltypeToString(URL_TYPES url_type);

//COMMANDS stringToCommand(std::string string);
//std::string commandToString(COMMANDS command);

//MODIFIERS stringToModifier(std::string string);
//std::string modifierToString(MODIFIERS modifier);

bool isCommand(std::string string);
bool isModifier(std::string string);

class inputStructure{
    private:
        std::optional<std::string> command;
        std::queue<std::string> modifiers;
        std::optional<std::filesystem::path> url;
        std::optional<enum URL_TYPES> urlType;
    public:
        inputStructure(int argc, char* argv[]);
        void print();
};