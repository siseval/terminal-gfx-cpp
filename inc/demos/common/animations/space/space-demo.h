#ifndef SPACE_DEMO_H
#define SPACE_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>
#include <demos/common/animations/space/body.h>
#include <demos/common/animations/space/planet.h>

namespace demos::common::animations::space
{

class SpaceDemo : public demos::common::core::GfxDemo
{

public:

    SpaceDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer), bodies(std::vector<std::shared_ptr<Body>>()) {}


    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const char input) override;

    std::vector<std::string> debug_text() override
    {
        return { "dt: " + std::to_string(last_frame_us / 1000) };
    }

    std::vector<std::shared_ptr<Body>> bodies;

private:

    std::shared_ptr<Planet> spawn_planet(const gfx::math::Vec2d position, const double radius, const double mass, const gfx::core::types::Color4 color, const gfx::math::Vec2d velocity = { 0, 0 });
    void spawn_planet(const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const double mass);
    void clear_bodies();

    void process(const double dt);
    void process_bodies(const double dt);

};

}

#endif // SPACE_DEMO_H
