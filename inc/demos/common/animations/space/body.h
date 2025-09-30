#ifndef BODY_H
#define BODY_H

#include <gfx/core/gfx-render-2D.h>
#include <gfx/primitives/circle-2D.h>
#include <gfx/math/vec2.h>
#include <demos/common/core/demo-utils.h>
#include <demos/common/animations/space/constants.h>

namespace demos::common::animations::space
{

class Body : public gfx::primitives::Circle2D
{

public:

    Body(const gfx::math::Vec2d position, const double radius, const double mass, const gfx::core::types::Color4 color) :
    mass(mass)
    {
        set_pos(position);
        set_radius(radius);
        set_color(color);
        set_fill(true);
    }

    virtual ~Body() {}

    gfx::math::Vec2d velocity;
    double mass = 1.0;

    void update_position(const double dt)
    {
        position += velocity * dt;
        set_pos(position);
        set_anchor({ 0.5, 0.5 });
    }

    void apply_gravity(const std::shared_ptr<Body> other, const double dt)
    {
        gfx::math::Vec2d direction { other->position - position };
        double distance { std::max(direction.length(), get_radius() + other->get_radius()) };
        if (distance <= 0.0)
        {
            return;
        }

        direction = direction.normalize();

        double force_magnitude { (constants::G * mass * other->mass) / (distance * distance) };
        gfx::math::Vec2d force { direction * force_magnitude };

        gfx::math::Vec2d acceleration { force / mass };
        velocity += acceleration * dt;
    }

};

}

#endif // BODY_H
