set(CURSES_ANIMATIONS_DEMO_SOURCES
    curses-animations-demo.cpp
)

add_executable(curses-animations-demo
    ${CURSES_ANIMATIONS_DEMO_SOURCES}
)

target_link_libraries(curses-animations-demo PUBLIC
    demos_curses
    demos_common_animations
    gfx
)

target_include_directories(curses-animations-demo PUBLIC
    ${INCLUDE_DIR}
    ${CURSES_SOURCE_DIR}/demos
)
