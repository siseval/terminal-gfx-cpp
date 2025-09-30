#include <demos/common/animations/space/space-demo.h>

namespace demos::common::animations::space
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;
using namespace demos::common::core;

void SpaceDemo::init()
{
    Vec2d resolution { get_resolution() };
    Vec2d center { resolution / 2 };

    clear_bodies();
    renderer->clear_items();
    renderer->get_render_surface()->clear_palette();

    // auto sun = spawn_planet(center, resolution.x * 0.1, 1000.0, { 255, 255, 0 }, { 0, 0 });
    auto p1 = spawn_planet(center + Vec2d { resolution.x * 0.3, 0}, resolution.x * 0.08, 4400.0, { 80, 255, 80 }, { -10, 20 });
    auto p2 = spawn_planet(center + Vec2d { -resolution.x * 0.3, -resolution.y * 0.4}, resolution.x * 0.03, 1100.0, { 80, 80, 255 }, { 15, -20 });
    auto p3 = spawn_planet(center + Vec2d { 0, resolution.y * 0.3 }, resolution.x * 0.02, 800.0, { 255, 80, 80 }, { 5, -10 });
}

void SpaceDemo::render_frame(const double dt)
{
    double t0 { utils::time_us() };
    double time_ms { t0 / 1000.0 };

    process(dt);

    renderer->draw_frame();
    last_frame_us = utils::time_us() - t0;
}

void SpaceDemo::process(const double dt)
{
    process_bodies(dt);
}

void SpaceDemo::process_bodies(const double dt)
{
    for (auto& body : bodies)
    {
        for (auto& other : bodies)
        {
            if (body == other)
            {
                continue;
            }
            body->apply_gravity(other, dt);
        }
        body->update_position(dt);
    }
}

std::shared_ptr<Planet> SpaceDemo::spawn_planet(const Vec2d position, const double radius, const double mass, const Color4 color, const Vec2d velocity)
{
    bodies.emplace_back(std::make_shared<Planet>(position, radius, mass, color, velocity));
    renderer->add_item(bodies.back());
    return dynamic_pointer_cast<Planet>(bodies.back());
}

void SpaceDemo::clear_bodies()
{
    bodies.clear();
    renderer->clear_items();
}

void SpaceDemo::handle_input(const char input)
{
    switch (input)
    {
        case 'c':
            bodies.clear();
            renderer->clear_items();
            break;

        default:
            break;
    }
}

void SpaceDemo::end()
{
    clear_bodies();
    renderer->clear_items();
}

}
