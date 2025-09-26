#ifndef GFX_DEMO_H
#define GFX_DEMO_H

#include <string>
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
    virtual void end() = 0;

    virtual std::vector<std::string> debug_text() { return {}; }

    inline void set_speed(const double s) { speed = s; }
    inline double get_speed() const { return speed; }

    inline std::shared_ptr<gfx::core::GfxRender2D> get_renderer() const { return renderer; }
    inline gfx::math::Vec2i get_resolution() const { return renderer->get_resolution(); }

    inline double get_fps() const { return CLOCKS_PER_SEC / last_frame_time; }

    inline std::vector<std::string> info_text()
    {
        std::vector<std::string> info;
        info.push_back("resolution: " + std::to_string(renderer->get_resolution().round().x) + "x" + std::to_string(renderer->get_resolution().round().y));
        info.push_back("fps: " + std::to_string(static_cast<int>(get_fps())));
        info.push_back("items: " + std::to_string(renderer->num_items()));

        return info;
    }

protected:

    std::shared_ptr<gfx::core::GfxRender2D> renderer;
    double last_frame_time = 0.0;
    double speed = 1.0;
};

}

#endif // GFX_DEMO_H
