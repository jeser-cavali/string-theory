#include "./build/_deps/harmony-src/harmony.hpp"
#include "color.hpp"

#include <iostream>

int main(int argc, char* argv[]){
    std::cout << Color::RED << "teste" << Color::RESET << std::endl;
    return 0;
}