cmake_minimum_required(VERSION 4.0)

project(
    player
    VERSION 0.1
    LANGUAGES CXX C
)

file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(player_core ${SOURCES})

target_include_directories(player_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(player main.cpp)

target_link_libraries(player PRIVATE player_core)