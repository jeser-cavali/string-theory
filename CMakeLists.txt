cmake_minimum_required(VERSION 4.0)

project(
    stringtheory
    VERSION 0.1
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(player_core ${SOURCES})

target_include_directories(player_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(stringtheory main_cli.cpp)
add_executable(harmony main_daemon.cpp)

target_link_libraries(stringtheory PRIVATE player_core)
target_link_libraries(harmony PRIVATE player_core)