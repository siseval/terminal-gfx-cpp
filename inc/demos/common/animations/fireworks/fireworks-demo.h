#ifndef FIREWORKS_DEMO_H
#define FIREWORKS_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>
#include <demos/common/animations/fireworks/firework.h>

namespace demos::common::animations::fireworks
{

class FireworksDemo : public GfxDemo
{

public:

    FireworksDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
    : GfxDemo(renderer) {}

    void init() override;
    void render_frame() override;
    void end() override;
    void handle_input(const char input) override;

    virtual std::vector<std::string> debug_text() override
    {
        return { 
            "dt: " + std::to_string(delta_time / CLOCKS_PER_SEC),
            "num fireworks: " + std::to_string(fireworks.size()),
            "velocity: " + std::to_string(fireworks.empty() ? 0.0 : fireworks.back().velocity.y)
        };
    }

private:

    void spawn_firework();

    int max_fireworks = 10;
    double last_spawn_time = 0.0;
    gfx::math::Vec2d margins = { 0.1, 0.1 };
    std::vector<Firework> fireworks;

};

}

#endif // FIREWORKS_DEMO_H
