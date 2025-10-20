#ifndef FIREWORK_H
#define FIREWORK_H

#include <gfx/core/render-2D.h>
#include <gfx/math/vec2.h>
#include <gfx/core/types/color4.h>
#include <demos/common/animations/fireworks/particle.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::fireworks
{

class Firework
{

public:

    void process(const double dt);
    void explode();

    struct firework_options
    {
        gfx::math::Vec2d size;

        int max_particles;
        double particle_size;
        double particle_lifespan_ms;
        double particle_speed;

        double smoke_size;
        double smoke_speed;
        double smoke_trail_interval_ms;
    };

    enum class State
    {
        Ascending,
        Exploding,
        Done
    };

    Firework(std::shared_ptr<gfx::core::Render2D> renderer, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const firework_options &options, const std::vector<gfx::core::types::Color4> colors) : 
        renderer(renderer), 
        position(position), 
        velocity(velocity), 
        start_velocity(velocity),
        size(options.size),
        max_particles(options.max_particles),
        particle_size(options.particle_size),
        particle_lifespan_ms(options.particle_lifespan_ms),
        particle_speed(options.particle_speed),
        smoke_size(options.smoke_size),
        smoke_speed(options.smoke_speed),
        smoke_trail_interval_ms(options.smoke_trail_interval_ms),
        colors(colors),
        state(State::Ascending) 
    {
        static std::vector<gfx::math::Vec2d> body_points { 
            { 0, 0 },
            { size.x, 0 },
            { size.x, size.y },
            { 0, size.y }
        };

        shape = renderer->create_polyline(position, body_points, { 255, 255, 255 }, size.x / 2);
        shape->set_anchor({ 0.5, 0.5 });
        shape->set_close(true);
        shape->set_fill(true);
        shape->set_rounded_corners(true);
        renderer->add_item(shape);

        static std::vector<gfx::math::Vec2d> cap_points {
            { 0, -size.y * 1.1 },
            { size.x * 0.3, 0 },
            { 0, size.y * 1.1 }
        };
        auto cap = renderer->create_polyline({ size.x, size.y / 2 }, cap_points, { 255, 0, 0 }, size.x / 2);
        cap->set_close(true);
        cap->set_fill(true);
        cap->set_rounded_corners(true);
        renderer->add_item(cap, shape);

        creation_time_ms = demos::common::core::utils::time_ms();
    }

    gfx::math::Vec2d start_velocity;

    int max_particles;
    double particle_size;
    double particle_lifespan_ms;
    double particle_speed;
    double particle_x_factor = 7.0;

    double smoke_size;
    double smoke_speed;
    gfx::core::types::Color4 smoke_color { 210, 210, 210 };
    double smoke_trail_interval_ms = 250.0;
    double last_smoke_time_ms;
    double smoke_angle_variation_degrees = 5.0;
    double smoke_x_factor = 5.0;
    std::vector<Particle> smoke_particles;

    std::shared_ptr<gfx::core::Render2D> renderer;
    std::shared_ptr<gfx::primitives::Polyline2D> shape;
    gfx::math::Vec2d position;
    gfx::math::Vec2d velocity;

    std::vector<gfx::core::types::Color4> colors;
    gfx::math::Vec2d size;

    std::vector<Particle> particles;
    State state;

    double creation_time_ms = 0.0;


private:

    void do_ascending(const double dt);
    void do_exploding(const double dt);

    void do_smoke(const double dt);
    void update_position(const double dt);
    void apply_gravity(const double dt);

};

}

#endif // FIREWORK_H
