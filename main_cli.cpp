//#include "./build/_deps/harmony-src/harmony.hpp"
#include "color.hpp"
#include "inputHandler.hpp"

int main(int argc, char* argv[]){
    try{
        auto i = inputStructure(argc, argv);
        i.print();
    } catch(std::runtime_error& e){
        printError(e.what());
    }
    return 0;
}