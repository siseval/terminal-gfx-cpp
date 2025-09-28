#include <demos/common/animations/fireworks/particle.h>

namespace demos::common::animations::fireworks
{

void Particle::process(const double dt)
{
    update_position(dt);
    apply_gravity(dt);

    if (colors.size() > 1)
    {
        double t = (clock() / static_cast<double>(CLOCKS_PER_SEC) - creation_time) / lifespan;
        shape->set_color(gfx::core::types::Color4::lerp(colors[0], colors[1], t));
    }

    shape->set_scale(gfx::math::Vec2d::lerp({ 1, 1 }, { 0.001, 0.001 }, (clock() / static_cast<double>(CLOCKS_PER_SEC) - creation_time) / lifespan));

    double time_now = clock() / static_cast<double>(CLOCKS_PER_SEC);
    if (time_now - creation_time >= lifespan)
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
    const double gravity = 9.81;
    velocity.y += gravity * dt;
}

}
