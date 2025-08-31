cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
project(curspp)
add_library(curspp STATIC
curspp.cpp
curspp-draw.cpp
)

add_executable(test
curspp.cpp
curspp-draw.cpp
gfx-context.cpp
gfx-render-2D.cpp
ellipse2D.cpp
test.cpp
)

find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})
target_link_libraries(curspp ${CURSES_LIBRARY})
target_link_libraries(test ${CURSES_LIBRARY})
