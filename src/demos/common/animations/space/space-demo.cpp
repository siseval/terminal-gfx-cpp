#include <demos/common/animations/space/space-demo.h>
#include <demos/common/animations/space/units.h>
#include <demos/common/animations/space/simulations.h>

namespace demos::common::animations::space
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;
using namespace demos::common::core;

void SpaceDemo::init()
{
    time_scale = 50000.0;
    clear_bodies();
    renderer->get_render_surface()->clear_palette();

    simulations::solar_system(*this);
}

void SpaceDemo::render_frame(const double dt)
{
    double t0 { utils::time_us() };
    double time_ms { t0 / 1000.0 };

    update_view(dt);
    physics_process(dt * time_scale);
    update_render_items();

    renderer->draw_frame();
    last_frame_us = utils::time_us() - t0;
}


void SpaceDemo::update_view(const double dt)
{
    if (get_tracked_body())
    {
        static const double Kp = track_speed;
        static const double Kd = 2.0 * std::sqrt(track_speed);

        Vec2d currentPos = get_anchor_world_pos();
        Vec2d currentVel = camera_velocity;

        Vec2d targetPos = get_tracked_body()->get_position();
        Vec2d targetVel = get_tracked_body()->get_velocity();

        Vec2d positionError = targetPos - currentPos;
        Vec2d velocityError = targetVel - currentVel;

        Vec2d acceleration = positionError * Kp + velocityError * Kd;

        camera_velocity += acceleration * dt;
    }
    else
    {
        camera_velocity *= std::pow(0.5, dt);
    }
    zoom_velocity *= std::pow(0.5, dt);
    zoom(1.0 + zoom_velocity * dt);

    set_view_pos(get_anchor_world_pos() + camera_velocity * dt);
}


void SpaceDemo::smooth_pan(const Vec2d direction)
{
    camera_velocity += direction * pan_speed * view_bounds.size().length();
}

void SpaceDemo::smooth_zoom(const double factor)
{
    zoom_velocity += (factor - 1.0) * 0.1;
}

void SpaceDemo::physics_process(const double dt)
{
    process_bodies(dt);
}

void SpaceDemo::process_bodies(const double dt)
{
    for (const auto& [body, item] : body_items)
    {
        for (const auto& [body2, item2] : body_items)
        {
            if (body == body2)
            {
                continue;
            }
            body->apply_gravity(body2, dt);
        }
        body->update_position(dt);
    }
}

void SpaceDemo::update_render_items()
{
    for (const auto& [body, item] : body_items)
    {
        Vec2d pos { units::metres_to_pixels(body->get_position() - view_bounds.min, view_bounds.size(), get_resolution()) };
        Vec2d radius { units::metres_to_pixels(body->get_radius(), view_bounds.size(), get_resolution()) };

        if (pos.x + radius.x < 0 || pos.x - radius.x > get_resolution().round().x ||
            pos.y + radius.y < 0 || pos.y - radius.y > get_resolution().round().y)
        {
            item->set_visible(false);
            continue;
        }

        item->set_visible(true);
        item->set_position(pos);
        item->set_radius(radius);
        item->set_color(body->get_color());
    }
}

std::shared_ptr<Body> SpaceDemo::spawn_body(const Vec2d position, const Vec2d velocity, const double radius, const double mass, const Color4 color)
{
    return spawn_body("", position, velocity, radius, mass, color);
}

std::shared_ptr<Body> SpaceDemo::spawn_body(const std::string name, const Vec2d position, const Vec2d velocity, const double radius, const double mass, const Color4 color)
{
    auto circle = std::make_shared<Ellipse2D>();
    circle->set_fill(true);
    circle->set_anchor({ 0.5, 0.5 });
    renderer->add_item(circle);

    auto body = std::make_shared<Body>(name, position, velocity, radius, mass, color);

    body_items.emplace(std::make_pair(body, circle));
    body_list.push_back(body);
    return body_items.begin()->first;
}

void SpaceDemo::clear_bodies()
{
    body_items.clear();
    body_list.clear();
    renderer->clear_items();
}

void SpaceDemo::handle_input(const char input)
{
    switch (input)
    {
        case 'c':
            clear_bodies();
            break;

        case 'K':
            time_scale *= 1.5;
            break;

        case 'J':
            time_scale /= 1.5;
            break;

        case 'w':
            untrack_body();
            smooth_pan({ 0, -1 });
            break;

        case 's':
            untrack_body();
            smooth_pan({ 0, 1 });
            break;

        case 'a':
            untrack_body();
            smooth_pan({ -1, 0 });
            break;

        case 'd':
            untrack_body();
            smooth_pan({ 1, 0 });
            break;

        case 'k':
            smooth_zoom(0.5);
            break;

        case 'j':
            smooth_zoom(1.5);
            break;

        case 'n':
            cycle_tracked_body();
            break;

        case 'p':
            cycle_tracked_body(-1);
            break;

        case 'u':
            tracked_body_index = -1;
            break;

        default:
            break;
    }
}

gfx::math::Vec2d SpaceDemo::get_screen_pos(const gfx::math::Vec2d world_pos)
{
    return units::metres_to_pixels(world_pos - view_bounds.min, view_bounds.size(), get_resolution());
}

gfx::math::Vec2d SpaceDemo::get_world_pos(const gfx::math::Vec2d screen_pos)
{
    Vec2d resolution { get_resolution() };
    return view_bounds.min + Vec2d {
        (screen_pos.x / resolution.x) * view_bounds.size().x,
        (screen_pos.y / resolution.y) * view_bounds.size().y
    };
}

void SpaceDemo::set_view_pos(const gfx::math::Vec2d pos)
{
    Vec2d size { view_bounds.size() };
    view_bounds.min = pos - size * view_anchor;
    view_bounds.max = view_bounds.min + size;
}

void SpaceDemo::set_view_size(const double width)
{
    Vec2d anchor_pos { view_bounds.min + view_bounds.size() * view_anchor };
    Vec2d resolution { get_resolution() };
    view_bounds.min = anchor_pos - Vec2d { width * view_anchor.x, (width * resolution.y / resolution.x) * view_anchor.y };
    view_bounds.max = view_bounds.min + Vec2d { width, (width * resolution.y / resolution.x) };
}

void SpaceDemo::zoom(const double factor)
{
    Vec2d anchor_pos { view_bounds.min + view_bounds.size() * view_anchor };
    view_bounds.min = anchor_pos - (anchor_pos - view_bounds.min) * factor;
    view_bounds.max = anchor_pos + (view_bounds.max - anchor_pos) * factor;
}

std::shared_ptr<Body> SpaceDemo::get_tracked_body()
{
    if (tracked_body_index < 0 || tracked_body_index >= body_list.size())
    {
        return nullptr;
    }
    return body_list[tracked_body_index];
}

void SpaceDemo::cycle_tracked_body(const int direction)
{
    tracked_body_index = (tracked_body_index + direction) % body_list.size();
}

void SpaceDemo::untrack_body()
{
    tracked_body_index = -1;
}


void SpaceDemo::end()
{
    clear_bodies();
}

}
