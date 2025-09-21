#ifndef GFX_DEMO_H
#define GFX_DEMO_H

#include <gfx/core/gfx-render-2D.h>

namespace demos::common
{

class GfxDemo
{

public:

    GfxDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : renderer(renderer) {}

    virtual void init() = 0;
    virtual void render_frame() = 0;
    virtual void handle_input(const char input) = 0;
    virtual std::vector<std::string> info_text() = 0;
    virtual void end() = 0;

    inline std::shared_ptr<gfx::core::GfxRender2D> get_renderer() const { return renderer; }
    inline gfx::math::Vec2i get_resolution() const { return renderer->get_resolution(); }

protected:

    std::shared_ptr<gfx::core::GfxRender2D> renderer;
};

}

#endif // GFX_DEMO_H
