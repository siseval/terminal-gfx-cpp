#include <demos/common/animations/fireworks/fireworks-demo.h>

namespace demos::common::animations::fireworks
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;


void FireworksDemo::init()
{

}

void FireworksDemo::render_frame()
{
    double t0 = static_cast<double>(clock());
    double dt_sec = delta_time / CLOCKS_PER_SEC;

    if (fireworks.size() < max_fireworks && (fireworks.empty() || (t0 - last_spawn_time) >= 0.5))
    {
        spawn_firework();
        last_spawn_time = t0;
    }

    std::vector<int> to_remove;
    for (int i = 0; i < fireworks.size(); i++)
    {
        fireworks[i].process(dt_sec);
        auto& firework = fireworks[i];
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
    delta_time = static_cast<double>(clock()) - t0;
}

void FireworksDemo::spawn_firework()
{
    Vec2d position = { 
        get_resolution().x * margins.x + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (get_resolution().x * (1.0 - 2.0 * margins.x)))),
        static_cast<double>(get_resolution().y)
    };
    double angle = (90.0 + (static_cast<double>(rand() % static_cast<int>(angle_variation * 2)) - angle_variation)) * (std::numbers::pi / 180.0);
    Vec2d velocity = Vec2d::from_angle(angle, -((firework_speed / 4) + (static_cast<double>(rand() % 1000)) / 1000) * (firework_speed));

    std::vector<Color4> colors = color_combinations[rand() % color_combinations.size()];
    fireworks.emplace_back(renderer, position, velocity, colors);
}

void FireworksDemo::handle_input(const char input)
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
