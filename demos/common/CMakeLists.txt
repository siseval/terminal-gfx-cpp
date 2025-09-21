add_subdirectory(interactive)

add_library(demos_common INTERFACE)

target_link_libraries(demos_common INTERFACE
    demos_common_interactive
)

target_include_directories(demos_common INTERFACE
    ${INCLUDE_DIR}
    ${CURSES_SOURCE_DIR}/demos
)
