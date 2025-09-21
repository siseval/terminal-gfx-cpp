set(DEMOS_CURSES_ANIMATIONS_SOURCES
    polylines-demo.cpp
)

add_executable(animations ${DEMOS_CURSES_ANIMATIONS_SOURCES})

target_link_libraries(animations PRIVATE
    gfx
    demos_curses
)

target_include_directories(animations PRIVATE
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/demos
)
