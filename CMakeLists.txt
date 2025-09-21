cmake_minimum_required(VERSION 3.10)

project(gfx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(gfx STATIC
    src/gfx/core/gfx-render-2D.cpp
    src/gfx/core/gfx-primitive-2D.cpp
    src/gfx/core/scene-graph-2D.cpp
    src/gfx/core/render-surface.cpp

    src/gfx/surfaces/curses-render-surface.cpp

    src/gfx/utils/rasterize.cpp
    src/gfx/utils/transform.cpp

    src/gfx/primitives/ellipse-2D.cpp
    src/gfx/primitives/polyline-2D.cpp
)

target_include_directories(gfx
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

find_package(Curses REQUIRED)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

add_executable(demo demo.cpp)

target_link_libraries(demo PRIVATE ${CURSES_LIBRARIES})
target_link_libraries(demo PRIVATE gfx)

