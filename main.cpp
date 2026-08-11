#include <iostream>

int main(int argc, char* argv[]){



    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";

    int MODIFIER_COUNT = argc - 3;

    if(MODIFIER_COUNT < 0){
        MODIFIER_COUNT = 0;
    }

    char* command;
    char* url;
    char* modifiers[MODIFIER_COUNT];

    if(argc < 3){
        std::cerr << RED << "ERROR: Missing arguments\nRemember the command structure: <command> <optional: modifier> <url>" << RESET;
        return 1;
    }

    if(argc == 3){
        command = argv[1];
        url = argv[2];
    } else{
        int last_item_index = argc - 1;
        int first_modifier_index = 2;
        int last_modifier_index = first_modifier_index + MODIFIER_COUNT; 

        int computed_modifier_count = 0;

        command = argv[1];
        url = argv[last_item_index];

        for(int i = first_modifier_index; i < last_modifier_index; i++){
            modifiers[computed_modifier_count] = argv[i];
            computed_modifier_count++;
        }
    }

    std::cout << "[command] " << command << "\n";
    if(MODIFIER_COUNT != 0){
        for(int i = 0; i < MODIFIER_COUNT; i++){
            std::cout << "  [modifier] " << modifiers[i] << "\n";
        }
    }
    std::cout << "[url] " << url << "\n";

    return 0;
}