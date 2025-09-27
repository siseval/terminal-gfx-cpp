cmake_minimum_required(VERSION 3.10)

project(gfx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(USE_CURSES "Use curses library as rendering backend" ON)
option(BUILD_DEMOS "Build demo applications" ON)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_subdirectory(src)
