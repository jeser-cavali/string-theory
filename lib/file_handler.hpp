#pragma once

#include <unordered_map>
#include <iostream>

enum argument_type{
    COMMAND,
    MODIFIER,
    URL,
    MUSIC,
    DIRECTORY
};

std::unordered_multimap<enum argument_type, std::string> map_arguments(int argc, char* argv[]);