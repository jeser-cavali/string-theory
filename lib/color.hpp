#pragma once

#include <string_view>
#include <iostream>

namespace Color {
    constexpr std::string_view RESET = "\033[0m";
    constexpr std::string_view RED = "\033[31m";
    constexpr std::string_view GREEN = "\033[32m";
    constexpr std::string_view YELLOW = "\033[33m";
    constexpr std::string_view BLUE = "\033[34m";
};

inline void printError(std::string_view string){
    std::cout << Color::RED << string << Color::RESET << std::endl;
};

inline void printAlert(std::string_view string){
    std::cout << Color::YELLOW << string << Color::RESET << std::endl;
};

inline void printSuccess(std::string_view string){
    std::cout << Color::GREEN << string << Color::RESET << std::endl;
};

inline void printTooltip(std::string_view string){
    std::cout << Color::BLUE << string << Color::RESET << std::endl;
};