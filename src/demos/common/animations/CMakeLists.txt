add_subdirectory(fireworks)
add_subdirectory(snake)
add_subdirectory(star)
add_subdirectory(space)

add_library(demos_common_animations INTERFACE)

target_link_libraries(demos_common_animations INTERFACE
    demos_common_animations_fireworks
    demos_common_animations_snake
    demos_common_animations_star
    demos_common_animations_space
)

target_include_directories(demos_common_animations INTERFACE
    ${INCLUDE_DIR}
)
