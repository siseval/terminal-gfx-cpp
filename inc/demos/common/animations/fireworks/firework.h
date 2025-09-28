#ifndef FIREWORK_H
#define FIREWORK_H

#include <gfx/core/gfx-render-2D.h>
#include <gfx/math/vec2.h>
#include <gfx/core/types/color4.h>
#include <demos/common/animations/fireworks/particle.h>

namespace demos::common::animations::fireworks
{

class Firework
{

public:

    void process(const double dt);
    void explode();

    enum class State
    {
        Ascending,
        Exploding,
        Done
    };

    Firework(std::shared_ptr<gfx::core::GfxRender2D> renderer, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const std::vector<gfx::core::types::Color4> &colors)
    : renderer(renderer), position(position), velocity(velocity), colors(colors), state(State::Ascending) 
    {
        std::vector<gfx::math::Vec2d> points = { { 0, 0 }, { size.x / 3, size.y / 2 }, { size.x, 0 }, { size.x / 3, -size.y / 2 } };
        shape = renderer->create_polyline(position, points, { 255, 255, 255 }, size.x / 2);
        shape->set_anchor({ 0.5, 0.5 });
        shape->set_close(true);
        shape->set_fill(true);
        shape->set_rounded_corners(true);
        renderer->add_item(shape);

        creation_time = clock() / static_cast<double>(CLOCKS_PER_SEC);
    }

    int max_particles = 70;
    double particle_size = 0.8;

    double smoke_size = 0.01;
    double smoke_speed = 1.0;
    gfx::core::types::Color4 smoke_color = { 200, 200, 200 };
    double smoke_trail_interval_sec = 0.05;
    double last_smoke_time = 0.0;
    std::vector<Particle> smoke_particles;

    std::shared_ptr<gfx::core::GfxRender2D> renderer;
    std::shared_ptr<gfx::primitives::Polyline2D> shape;
    gfx::math::Vec2d position;
    gfx::math::Vec2d velocity;

    bool gradient = false;
    std::vector<gfx::core::types::Color4> colors;
    gfx::math::Vec2d size = { 1.5, 0.3 };

    std::vector<Particle> particles;
    State state;

    double lifespan = 5.0;
    double creation_time = 0.0;


private:

    void do_ascending(const double dt);
    void do_exploding(const double dt);

    void do_smoke(const double dt);
    void update_position(const double dt);
    void apply_gravity(const double dt);

};

}

#endif // FIREWORK_H
