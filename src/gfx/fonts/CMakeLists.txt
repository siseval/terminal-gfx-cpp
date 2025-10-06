set(GFX_FONTS_SOURCES
    font-manager-ttf.cpp
    font-ttf.cpp
)

add_library(gfx_fonts STATIC ${GFX_FONTS_SOURCES})

target_link_libraries(gfx_fonts PUBLIC
    gfx_core
)

target_include_directories(gfx_fonts PUBLIC
        ${INCLUDE_DIR}
)

