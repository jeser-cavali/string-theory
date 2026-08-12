#include "file_handler.hpp"
#include "color.hpp"

#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>

int main(int argc, char* argv[]){

    std::unordered_multimap<enum argument_type, std::string> argument_map;

    try{
        argument_map = map_arguments(argc, argv);
    } catch(const std::runtime_error& e){
        std::cout << Color::RED << "ERROR: " << e.what() << Color::RESET << std::endl;
    }

    for(const auto& [key, value] : argument_map){
        std::cout << key << ": " << value << "\n";
    }

    return 0;
}