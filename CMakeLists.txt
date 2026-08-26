cmake_minimum_required(VERSION 4.0)

include(FetchContent)

project(
    stringtheory
    VERSION 0.1
    LANGUAGES CXX C
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FetchContent_Declare(
    harmony
    GIT_REPOSITORY https://github.com/jeser-cavali/Harmony.git
    GIT_TAG main
)

file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c"
)

add_library(player_core ${SOURCES})

target_include_directories(player_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(stringtheory main_cli.cpp)
#add_executable(harmonyEngine main_daemon.cpp)

FetchContent_MakeAvailable(harmony)

target_link_libraries(stringtheory PRIVATE player_core)
#target_link_libraries(harmonyEngine PRIVATE player_core)
#target_link_libraries(player_core PRIVATE harmony)