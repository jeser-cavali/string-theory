#include "file_handler.hpp"
#include "color.hpp"

#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>

int main(int argc, char* argv[]){

    std::unordered_map<enum argument_type, std::string> argument_map;

    try{
        argument_map = map_arguments(argc, argv);
    } catch(const std::runtime_error& e){
        std::cout << Color::RED << "ERROR: " << e.what() << Color::RESET << std::endl;
    }

    /*
    TODO(make custom enum? for console colors);

    const std::string RESET = "\033[0m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string BLUE = "\033[34m";
    */

    return 0;
}