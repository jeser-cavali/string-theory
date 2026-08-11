#include <iostream>

int main(int argc, char* argv[]){

    int modifier_count = argc - 3;

    char* command;
    char* url;
    char* modifiers[modifier_count];

    if(argc == 3){
        command = argv[1];
        url = argv[2];
    } else{
        int last_item_index = argc - 1;
        int first_modifier_index = 2;
        int last_modifier_index = first_modifier_index + modifier_count; 

        int computed_modifier_count = 0;

        command = argv[1];
        url = argv[last_item_index];

        for(int i = first_modifier_index; i < last_modifier_index; i++){
            modifiers[computed_modifier_count] = argv[i];
            computed_modifier_count++;
        }
    }

    std::cout << "[command] " << command << "\n";
    if(modifier_count != 0){
        for(int i = 0; i < modifier_count; i++){
            std::cout << "  [modifier] " << modifiers[i] << "\n";
        }
    }
    std::cout << "[url] " << url << "\n";

    return 0;
}