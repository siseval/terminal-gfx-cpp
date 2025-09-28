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

    double firework_speed = 10.0;
    double angle_variation = 8.0;
    int max_fireworks = 10;
    double last_spawn_time = 0.0;
    gfx::math::Vec2d margins = { 0.1, 0.1 };
    std::vector<Firework> fireworks;

    std::vector<std::vector<gfx::core::types::Color4>> color_combinations = {
        { { 240, 40, 40 }, { 255, 90, 90 } },
        { { 240, 140, 0 }, { 255, 210, 0 } },
        { { 255, 255, 0 }, { 220, 220, 0 } },
        // { { 255, 180, 0 }, { 100, 180, 255 } },
        // { { 255, 255, 0 }, { 255, 0, 255 } },
        // { { 255, 25, 0 }, { 255, 180, 0 } },
        // { { 0, 255, 255 }, { 0, 255, 0 } },
    };

};

}

#endif // FIREWORKS_DEMO_H
