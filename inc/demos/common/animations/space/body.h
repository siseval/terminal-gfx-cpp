#ifndef BODY_H
#define BODY_H

#include <gfx/core/types/color4.h>
#include <gfx/math/vec2.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::space
{

class Body
{

public:

    Body(std::string name, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const double radius, const double mass, const gfx::core::types::Color4 color) :
        name(name),
        position(position),
        velocity(velocity),
        radius(radius),
        mass(mass),
        color(color) {}

    void update_position(const double dt);
    void apply_gravity(const std::shared_ptr<Body> other, const double dt);

    void set_name(const std::string n) { name = n; }
    std::string get_name() const { return name; }

    void set_position(const gfx::math::Vec2d pos) { position = pos; }
    gfx::math::Vec2d get_position() const { return position; }

    void set_velocity(const gfx::math::Vec2d vel) { velocity = vel; }
    gfx::math::Vec2d get_velocity() const { return velocity; }

    void set_radius(const double r) { radius = r; }
    double get_radius() const { return radius; }

    void set_mass(const double m) { mass = m; }
    double get_mass() const { return mass; }

    void set_color(const gfx::core::types::Color4 col) { color = col; }
    gfx::core::types::Color4 get_color() const { return color; }



protected:

    std::string name;

    gfx::math::Vec2d position;
    gfx::math::Vec2d velocity;

    double radius;
    double mass;

    gfx::core::types::Color4 color;
};

}

#endif // BODY_H
