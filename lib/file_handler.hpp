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

bool check_valid_filetype(std::string string);

std::unordered_multimap<enum argument_type, std::string> map_arguments(int argc, char* argv[]);

std::string translate_enum(enum argument_type enum_item);