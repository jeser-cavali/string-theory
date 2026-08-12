#pragma once

#include <string_view>

namespace Color {
    constexpr std::string_view RESET = "\033[0m";
    constexpr std::string_view RED = "\033[31m";
    constexpr std::string_view GREEN = "\033[32m";
    constexpr std::string_view YELLOW = "\033[33m";
    constexpr std::string_view BLUE = "\033[34m";
}