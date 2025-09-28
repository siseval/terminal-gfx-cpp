#ifndef PARTICLE_H
#define PARTICLE_H

#include <gfx/core/gfx-render-2D.h>
#include <gfx/primitives/ellipse-2D.h>
#include <gfx/math/vec2.h>
#include <gfx/core/types/color4.h>

namespace demos::common::animations::fireworks
{

class Particle
{

public:

    Particle(std::shared_ptr<gfx::core::GfxRender2D> renderer, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const gfx::math::Vec2d size, const std::vector<gfx::core::types::Color4> &colors, const double lifespan)
    : renderer(renderer), position(position), velocity(velocity), size(size), colors(colors), lifespan(lifespan)
    {
        shape = renderer->create_ellipse(position, size, colors[0]);
        shape->set_fill(true);
        renderer->add_item(shape);
        creation_time = clock() / static_cast<double>(CLOCKS_PER_SEC);
    }

    void process(const double dt);
    bool done = false;

private:

    void update_position(const double dt);
    void apply_gravity(const double dt);

    std::shared_ptr<gfx::core::GfxRender2D> renderer;
    std::shared_ptr<gfx::primitives::Ellipse2D> shape;
    gfx::math::Vec2d size;
    gfx::math::Vec2d position;
    gfx::math::Vec2d velocity;
    std::vector<gfx::core::types::Color4> colors;

    double lifespan = 0.0;
    double creation_time = 0.0;

};

}

#endif // PARTICLE_H
