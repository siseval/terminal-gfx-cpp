set(DEMOS_COMMON_ANIMATIONS_SOURCES
    star-demo.cpp
    snake-demo.cpp
)

add_library(demos_common_animations STATIC ${DEMOS_COMMON_ANIMATIONS_SOURCES})

target_link_libraries(demos_common_animations PRIVATE
    gfx
)

target_include_directories(demos_common_animations PUBLIC
    ${INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/demos
)
