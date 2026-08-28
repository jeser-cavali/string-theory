#pragma once

#include <filesystem>
#include <optional>
#include <queue>

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

enum URL_TYPES{
    MUSIC,
    DIRECTORY
};

COMMANDS stringToCommand(std::string string);
std::string commandToString(COMMANDS command);

MODIFIERS stringToModifier(std::string string);
std::string modifierToString(MODIFIERS modifier);

bool isCommand(std::string string);
bool isModifier(std::string string);

class inputStructure{
    private:
        std::optional<enum COMMANDS> command;
        std::queue<enum MODIFIERS> modifiers;
        std::optional<std::filesystem::path> url;
        std::optional<enum URL_TYPES> urlType;
    public:
        inputStructure(int argc, char* argv[]);
};