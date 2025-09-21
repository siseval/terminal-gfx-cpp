if(USE_CURSES)
add_subdirectory(curses)
endif()

add_library(gfx_surfaces INTERFACE)

if(TARGET gfx_surfaces_curses)
target_link_libraries(gfx_surfaces INTERFACE gfx_surfaces_curses)
endif()

target_include_directories(gfx_surfaces INTERFACE
        ${INCLUDE_DIR}
)
