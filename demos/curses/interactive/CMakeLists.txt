set(DEMOS_CURSES_INTERACTIVE_SOURCES
    main.cpp
)

add_executable(interactive ${DEMOS_CURSES_INTERACTIVE_SOURCES})

target_link_libraries(interactive PRIVATE
    gfx
    demos_curses
)

target_include_directories(interactive PRIVATE
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/demos
)
