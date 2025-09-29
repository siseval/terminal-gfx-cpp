#include <demos/common/animations/fireworks/particle.h>

namespace demos::common::animations::fireworks
{

using namespace demos::common::core;

void Particle::process(const double dt)
{
    shape->set_rotation_degrees(velocity.angle_degrees());

    double t { (utils::time_ms() - creation_time_ms) / lifespan_ms };
    if (colors.size() > 1)
    {
        shape->set_color(gfx::core::types::Color4::lerp(colors[0], colors[1], t));
    }

    if (t < 0.2)
    {
        shape->set_scale(gfx::math::Vec2d::lerp({ 0.001, 0.001 }, { 1, 1 }, t * 5));
    }
    else
    {
        shape->set_scale(gfx::math::Vec2d::lerp({ 1, 1 }, { 0.001, 0.001 }, t - 0.2));
    }

    update_position(dt);
    apply_gravity(dt);

    if (utils::time_ms() - creation_time_ms >= lifespan_ms)
    {
        renderer->remove_item(shape);
        done = true;
    }
}

void Particle::update_position(const double dt)
{
    position += velocity * dt;
    shape->set_pos(position);
}

void Particle::apply_gravity(const double dt)
{
    const double gravity = 5.0;
    velocity.y += gravity * dt;
}

}
