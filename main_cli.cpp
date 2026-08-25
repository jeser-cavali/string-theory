#include "input_parser.hpp"
#include "color.hpp"
#include "harmony_engine.hpp"
#include "./build/_deps/harmony-src/harmony.hpp"

#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <filesystem>
#include <chrono>
#include <windows.h>
#include <tlhelp32.h>
#include <string_view>

bool IsProcessRunning(std::wstring_view processName) {
    bool exists = false;
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(PROCESSENTRY32W);

    // Take a snapshot of all running processes
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
    if (snapshot == INVALID_HANDLE_VALUE) return false;

    // Retrieve information about the first process
    if (Process32FirstW(snapshot, &entry)) {
        do {
            // Compare current process name against target
            if (processName == entry.szExeFile) {
                exists = true;
                break;
            }
        } while (Process32NextW(snapshot, &entry)); // Move to next process
    }

    CloseHandle(snapshot);
    return exists;
}

void start_process(std::string string){
    char* cmd = const_cast<char*>(string.c_str());

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    BOOL success = CreateProcess(
    NULL,           // Application name (can be NULL if passed in cmd)
    cmd,            // Command line arguments (must be writable)
    NULL,           // Process handle not inheritable
    NULL,           // Thread handle not inheritable
    FALSE,          // Disable handle inheritance
    0,              // No creation flags
    NULL,           // Use parent's environment block
    NULL,           // Use parent's starting directory
    &si,            // Pointer to STARTUPINFO structure
    &pi             // Pointer to PROCESS_INFORMATION structure
    );
}

int main(int argc, char* argv[]){

    //benchmark start
    auto benchamrk_start = std::chrono::high_resolution_clock::now();

    try{
        InputStructure i = InputStructure(argc, argv);

        std::cout << "Starting..." << std::endl;

        if(!IsProcessRunning(L"harmony.exe")){
            start_process("harmony.exe");
            std::cout << "Starting Harmony engine..." << std::endl;
        } else{
            std::cout << "System is in harmony..." << std::endl;
        }

        auto benchmark_end = std::chrono::high_resolution_clock::now();
        auto benchamrk_results = std::chrono::duration_cast<std::chrono::microseconds>(benchamrk_start - benchmark_end).count();
        std::cout << "<execution duration> " << benchamrk_results << "ms\n";
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