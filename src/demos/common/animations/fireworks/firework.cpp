#include <numbers>
#include <demos/common/animations/fireworks/firework.h>

namespace demos::common::animations::fireworks
{

using namespace gfx::core::types;
using namespace gfx::math;

void Firework::process(const double dt)
{
    switch (state)
    {
        case State::Ascending:
            do_ascending(dt);
            break;

        case State::Exploding:
            do_exploding(dt);
            break;

        default:
            break;
    }
}

void Firework::explode()
{
    state = State::Exploding;
    renderer->remove_item(shape);

    int num_particles = max_particles / 2 + rand() % (max_particles / 2);
    for (int i = 0; i < num_particles; ++i)
    {
        double angle = (std::rand() % 360) * (std::numbers::pi / 180.0);
        double speed = 0.5 + 10 * static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (2.0 - 0.5)));
        Vec2d velocity = Vec2d::from_angle(angle, speed) - Vec2d { 0, 5 };
        Vec2d size = Vec2d::create(static_cast<double>(std::rand() % 1000) / 1000 * particle_size);

        double lifespan = 1.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (3.0 - 1.0)));
        std::vector<Color4> color = gradient ? colors : std::vector<Color4> { colors[rand() % colors.size()] };
        particles.emplace_back(renderer, position, velocity, size, color, lifespan);
    }
}

void Firework::do_ascending(const double dt)
{
    shape->set_rotation(velocity.angle());
    update_position(dt);
    apply_gravity(dt);

    do_smoke(dt);

    for (auto& particle : smoke_particles)
    {
        particle.process(dt);
    }

    if (velocity.y >= 0.0)
    {
        explode();
    }
}

void Firework::do_exploding(const double dt)
{
    for (auto& particle : particles)
    {
        particle.process(dt);
    }
    for (auto& particle : smoke_particles)
    {
        particle.process(dt);
    }
    double time_now = clock() / static_cast<double>(CLOCKS_PER_SEC);

    particles.erase(std::remove_if(particles.begin(), particles.end(), 
                                   [](const Particle& p) { return p.done; }),
                    particles.end());
    smoke_particles.erase(std::remove_if(smoke_particles.begin(), smoke_particles.end(), 
                                          [](const Particle& p) { return p.done; }),
                          smoke_particles.end());

    if (particles.empty() && smoke_particles.empty())
    {
        state = State::Done;
    }
}

void Firework::do_smoke(const double dt)
{
    if (static_cast<double>(std::clock()) / CLOCKS_PER_SEC - last_smoke_time > smoke_trail_interval_sec)
    {
        double angle = -velocity.angle() + (std::rand() % 30) * (std::numbers::pi / 180.0);
        double speed = (smoke_speed / 2) + (static_cast<double>(std::rand() % 1000) / 1000) * smoke_speed / 2;
        Vec2d velocity = Vec2d::from_angle(angle, speed);
        Vec2d size = Vec2d::create(smoke_size * (0.5 + static_cast<double>(std::rand() % 1000) / 2000.0));
        double lifespan = 1.0 + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (3.0 - 1.0)));
        smoke_particles.emplace_back(renderer, position, velocity, size, std::vector<Color4> { smoke_color }, lifespan);
        last_smoke_time = static_cast<double>(std::clock()) / CLOCKS_PER_SEC;
    }

}

void Firework::update_position(const double dt)
{
    position += velocity * dt;
    shape->set_pos(position);
}

void Firework::apply_gravity(const double dt)
{
    const double gravity = 9.81;
    velocity.y += gravity * dt;
}

}
