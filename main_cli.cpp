#include "input_parser.hpp"
#include "color.hpp"
#include "harmony_engine.hpp"

#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>
#include <chrono>

int main(int argc, char* argv[]){

    //benchmark start
    auto benchamrk_start = std::chrono::high_resolution_clock::now();

    try{
        InputStructure i = InputStructure(argc, argv);
        auto benchmark_end = std::chrono::high_resolution_clock::now();
        auto benchamrk_results = std::chrono::duration_cast<std::chrono::microseconds>(benchamrk_start - benchmark_end).count();
        std::cout << "<execution duration> " << benchamrk_results << "ms\n";
        i.print();
    } catch(const std::runtime_error& e){
        std::cout << Color::RED << "ERROR: " << e.what() << Color::RESET << std::endl;
    }
    
    //std::unordered_multimap<enum argument_type, std::string> argument_map;

    /*
    try{
        argument_map = map_arguments(argc, argv);
    } catch(const std::runtime_error& e){
        std::cout << Color::RED << "ERROR: " << e.what() << Color::RESET << std::endl;
    }
    */

    /*
    //print argument_map
    for(const auto& [key, value] : argument_map){
        std::cout << translate_argument_type(key) << ": " << value << std::endl;
    }
    */

    //music component first implementation
    /*
    try{
        Harmony h = Harmony();
        h.play_directory(argument_map);
    } catch(const std::runtime_error& e){
        std::cout << Color::RED << "ERROR: " << e.what() << Color::RESET << std::endl;
    }
    */

    return 0;
}