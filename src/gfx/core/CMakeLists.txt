set(GFX_CORE_SOURCES
    primitive-2D.cpp
    render-2D.cpp
    render-surface.cpp
    scene-graph-2D.cpp
    shader-2D.cpp
)

add_library(gfx_core STATIC ${GFX_CORE_SOURCES})

target_include_directories(gfx_core PUBLIC
    ${INCLUDE_DIR}
)

