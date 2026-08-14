#include "file_handler.hpp"
#include "color.hpp"

#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>
#include <chrono>

int main(int argc, char* argv[]){

    //benchmark start
    auto benchamrk_start = std::chrono::high_resolution_clock::now();

    std::unordered_multimap<enum argument_type, std::string> argument_map;

    try{
        argument_map = map_arguments(argc, argv);
    } catch(const std::runtime_error& e){
        std::cout << Color::RED << "ERROR: " << e.what() << Color::RESET << std::endl;
    }

    for(const auto& [key, value] : argument_map){
        std::cout << translate_enum(key) << ": " << value << std::endl;
    }

    //benchmark end
    auto benchmark_end = std::chrono::high_resolution_clock::now();
    auto benchamrk_results = std::chrono::duration_cast<std::chrono::microseconds>(benchamrk_start - benchmark_end).count();
    std::cout << "<execution duration> " << benchamrk_results << "ms\n";

    return 0;
}