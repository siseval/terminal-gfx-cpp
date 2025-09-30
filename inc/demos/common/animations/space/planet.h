#ifndef PLANET_H
#define PLANET_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/animations/space/body.h>

namespace demos::common::animations::space
{

class Planet : public Body
{

public:

    Planet(const gfx::math::Vec2d position, const double radius, const double mass, const gfx::core::types::Color4 color) :
    Body(position, radius, mass, color)
    {
        velocity = gfx::math::Vec2d::zero();
    }

    Planet(const gfx::math::Vec2d position, const double radius, const double mass, const gfx::core::types::Color4 color, const gfx::math::Vec2d velocity) :
    Planet(position, radius, mass, color)
    {
        this->velocity = velocity;
    }

};

}

#endif // PLANET_H
