cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
project(curspp)
add_library(curspp STATIC
curspp.cpp
)

add_executable(test
curspp.cpp
gfx-context-2D.cpp
gfx-render-2D.cpp
gfx-primitive-2D.cpp
ellipse-2D.cpp
polyline-2D.cpp
gfx-rasterize.cpp
test.cpp
)

find_package(Curses REQUIRED)
set(CURSES_NEED_NCURSES TRUE)
set(CURSES_NEED_WIDE TRUE)

include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(curspp ${CURSES_LIBRARY})
target_link_libraries(test ${CURSES_LIBRARY})
