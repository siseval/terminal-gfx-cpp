#include <demos/common/animations/fireworks/fireworks-demo.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::fireworks
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;
using namespace demos::common::core;


void FireworksDemo::init()
{
    Vec2i resolution { get_resolution() };
    spawn_margins = resolution * 0.1;
    firework_speed = std::sqrt(9.81 * resolution.y);

    options.size = { resolution.x * 0.005, resolution.x * 0.0005 };

    options.max_particles = 70;
    options.particle_size = resolution.x * 0.001;
    options.particle_lifespan_ms = 2000.0;
    options.particle_speed = firework_speed * 0.6;

    options.smoke_size = resolution.x * 0.001;
    options.smoke_speed = firework_speed * 0.4;
    options.smoke_trail_interval_ms = 25;
}

void FireworksDemo::render_frame(const double dt)
{
    double t0 { utils::time_us() };
    double time_ms { t0 / 1000.0 };

    if (fireworks.size() < max_fireworks && (fireworks.empty() || (time_ms - last_spawn_time_ms) >= spawn_interval_ms))
    {
        spawn_firework();
        last_spawn_time_ms = time_ms;
    }

    std::vector<int> to_remove;
    for (int i = 0; i < fireworks.size(); ++i)
    {
        fireworks[i].process(dt);
        auto& firework { fireworks[i] };
        if (firework.state == Firework::State::Done)
        {
            to_remove.push_back(i);
        }
    }
    for (auto index : to_remove)
    {
        fireworks.erase(fireworks.begin() + index);
    }

    renderer->draw_frame();
}

void FireworksDemo::spawn_firework()
{
    Vec2d position {
        static_cast<double>(utils::random_int(spawn_margins.x, get_resolution().x - spawn_margins.x)),
        static_cast<double>(get_resolution().y)
    };

    double angle { utils::random_double(-angle_variation, angle_variation) - 90 };
    Vec2d velocity { Vec2d::from_angle_degrees(angle, utils::random_double(firework_speed * 0.75, firework_speed * 1.25)) };

    std::vector<Color4> colors { color_combinations[rand() % color_combinations.size()] };
    fireworks.emplace_back(renderer, position, velocity, options, colors);
}

void FireworksDemo::handle_input(const int input)
{
    switch (input)
    {
        case 'f':
            spawn_firework();
            break;
        case '+':
            max_fireworks += 1;
            break;
        case '-':
            if (max_fireworks > 1)
            {
                max_fireworks -= 1;
            }
            break;
    }
}


void FireworksDemo::end()
{
    fireworks.clear();
    renderer->clear_items();
}

}
