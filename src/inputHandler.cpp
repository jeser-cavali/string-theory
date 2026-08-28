#include "inputHandler.hpp"

#include <unordered_map>
#include <array>

COMMANDS stringToCommand(std::string string){
    static const std::unordered_map<std::string_view, enum COMMANDS> ref = {
        {"play", COMMANDS::PLAY},
        {"pause", COMMANDS::PAUSE},
        {"skip", COMMANDS::SKIP},
        {"stop", COMMANDS::STOP}
    };

    if(ref.contains(string)){
        return ref.at(string);
    }
    
    throw std::runtime_error("STRING IS NOT A COMMAND");
}

std::string commandToString(COMMANDS command){
    std::array ref = {
        "play",
        "pause",
        "skip",
        "stop"
    };
    return ref.at(command);
}

MODIFIERS stringToModifier(std::string string){
    std::unordered_map<std::string_view, MODIFIERS> ref = {
        {"loop", MODIFIERS::LOOP},
        {"rand", MODIFIERS::RAND}
    };
    return ref.at(string);
}

std::string modifierToString(MODIFIERS modifier){
    std::array ref = {
        "loop",
        "rand"
    };
    return ref.at(modifier);
}

bool isCommand(std::string string){
    return (
        stringToCommand(string) == COMMANDS::PLAY ||
        stringToCommand(string) == COMMANDS::PAUSE ||
        stringToCommand(string) == COMMANDS::SKIP ||
        stringToCommand(string) == COMMANDS::STOP
    );
}

bool isModifier(std::string string){
    return (
        string.compare("loop") ||
        string.compare("rand")
    );
}

inputStructure::inputStructure(int argc, char* argv[]){
    if(argc <= 1){
        throw std::runtime_error("NO ARGUMENTS PROVIDED");
    }

    for(int i = 1; i < argc; i++){
        if(isCommand(argv[i]) && !command.has_value()){
            command = stringToCommand(argv[i]);
        }

        if(isModifier(argv[i])){
            modifiers.emplace(stringToModifier(argv[i]));
        }

        if(std::filesystem::exists(argv[i])){
            url = argv[i];

            if(std::filesystem::is_regular_file(argv[i])){
                urlType = URL_TYPES::MUSIC;
            } else if(std::filesystem::is_directory(argv[i])){
                urlType = URL_TYPES::DIRECTORY;
            }
        }
    }
}