#ifndef PARTICLE_H
#define PARTICLE_H

#include <gfx/core/render-2D.h>
#include <gfx/primitives/ellipse-2D.h>
#include <gfx/math/vec2.h>
#include <gfx/core/types/color4.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::fireworks
{

class Particle
{

public:

    Particle(std::shared_ptr<gfx::core::Render2D> renderer, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const gfx::math::Vec2d size, const std::vector<gfx::core::types::Color4> &colors, const double lifespan)
    : renderer(renderer), position(position), velocity(velocity), size(size), colors(colors), lifespan_ms(lifespan)
    {
        shape = renderer->create_ellipse(position, size, colors[0]);
        shape->set_filled(true);
        renderer->add_item(shape);
        creation_time_ms = demos::common::core::utils::time_ms();
    }

    void process(const double dt);
    bool done = false;

private:

    void update_position(const double dt);
    void apply_gravity(const double dt);

    std::shared_ptr<gfx::core::Render2D> renderer;
    std::shared_ptr<gfx::primitives::Ellipse2D> shape;
    gfx::math::Vec2d size;
    gfx::math::Vec2d position;
    gfx::math::Vec2d velocity;
    std::vector<gfx::core::types::Color4> colors;

    double lifespan_ms = 0.0;
    double creation_time_ms = 0.0;

};

}

#endif // PARTICLE_H
