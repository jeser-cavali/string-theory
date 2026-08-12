#pragma once

#include <unordered_map>
#include <iostream>

enum argument_type{
    UNCLASSIFIED,
    COMMAND,
    MODIFIER,
    URL,
    MUSIC,
    DIRECTORY
};

std::unordered_multimap<enum argument_type, std::string> map_arguments(int argc, char* argv[]);