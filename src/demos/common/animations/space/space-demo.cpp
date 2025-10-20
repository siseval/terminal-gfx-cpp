#include <algorithm>
#include <demos/common/animations/space/space-demo.h>
#include <demos/common/animations/space/units.h>
#include <demos/common/animations/space/simulations.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::space
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;
using namespace demos::common::core;

void SpaceDemo::init()
{
    time_scale = 0.01;
    clear_bodies();
    renderer->get_render_surface()->clear_palette();
    hovered_body = nullptr;

    std::vector<Vec2d> bracket_points { { 20, 0 }, { 0, 20 }, { 0, 90, }, { 20, 110 } };
    left_bracket = renderer->create_polyline({ 0, 0 }, bracket_points, Color4 { 255, 255, 255 }, min_bracket_thickness);
    right_bracket = renderer->create_polyline({ 0, 0 }, bracket_points, Color4 { 255, 255, 255 }, min_bracket_thickness);
    right_bracket->set_rotation(std::numbers::pi);
    left_bracket->set_anchor({ 0.5, 0.5 });
    right_bracket->set_anchor({ 0.5, 0.5 });
    left_bracket->set_rounded_corners(true);
    right_bracket->set_rounded_corners(true);
    renderer->add_item(left_bracket);
    renderer->add_item(right_bracket);

    simulations::solar_system(*this);
}

void SpaceDemo::render_frame(const double dt)
{
    double t0 { utils::time_us() };
    double time_ms { t0 / 1000.0 };

    t_sec += dt;

    physics_process(dt * time_scale);

    double time_lerp { std::min(time_accumulator / PHYSICS_TIME_STEP, 1.0) };
    handle_camera(dt, time_lerp);
    update_hovered_brackets(time_lerp);
    update_render_items(time_lerp);
    handle_hovered_body(dt, time_lerp);

    renderer->draw_frame();
    last_frame_us = utils::time_us() - t0;
}

void SpaceDemo::handle_camera(const double dt, const double time_lerp)
{
    camera.end_pos = camera.cur_pos;
    if (camera.state == Camera::State::Free)
    {
        untrack_body();
    }

    if (get_tracked_body())
    {
        RenderBody render_body { body_items.at(get_tracked_body()) };
        camera.end_pos = body_interpolated_pos(get_tracked_body(), time_lerp);
    }

    if (camera.state == Camera::State::Transitioning && previous_tracked_body)
    {
        camera.start_pos = body_interpolated_pos(previous_tracked_body, time_lerp);
    }
    camera.process(dt);
    set_view_pos(camera.cur_pos);
    set_view_size(camera.size_cur.x);
}

void SpaceDemo::handle_hovered_body(const double dt, const double time_lerp)
{
    auto previous_render_body { hovered_body };
    if (hovered_time >= hovered_poll_time)
    {
        hovered_body = get_closest_body_screenspace(mouse_pos, 50.0, 2.0, time_lerp);
    }

    if (hovered_body != previous_render_body)
    {
        hovered_time = 0.0;
    }
    else if (hovered_time <= 1.0)
    {
        hovered_time += dt / bracket_grow_time;
    }
    else
    {
        hovered_time = 1.0;
    }
}

void SpaceDemo::physics_process(const double dt)
{
    time_accumulator += dt;
    int steps { 0 };

    while (time_accumulator >= PHYSICS_TIME_STEP && steps < MAX_STEPS_PER_FRAME)
    {
        for (auto& [body, render] : body_items)
        {
            render.previous_pos = body->get_position();
        }
        process_bodies(PHYSICS_TIME_STEP);
        time_accumulator -= PHYSICS_TIME_STEP;
        steps++;
    }
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
            if (body->is_locked())
            {
                continue;
            }
            body->apply_gravity(body2, dt);
        }
        body->update_position(dt);
    }
}

void SpaceDemo::update_render_items(const double time_lerp)
{
    for (const auto& [body, render] : body_items)
    {
        auto ellipse { render.ellipse };

        Vec2d pos_lerp { Vec2d::lerp(render.previous_pos, body->get_position(), time_lerp) };
        Vec2d pos { units::metres_to_pixels(pos_lerp - view_bounds.min, view_bounds.size(), get_resolution()) };
        Vec2d radius { units::metres_to_pixels(body->get_radius(), view_bounds.size(), get_resolution()) };

        if (pos.x + radius.x < 0 || pos.x - radius.x > get_resolution().round().x ||
            pos.y + radius.y < 0 || pos.y - radius.y > get_resolution().round().y)
        {
            ellipse->set_visible(false);
            continue;
        }

        ellipse->set_rotation(ellipse->get_rotation() + 0.005);
        ellipse->set_visible(true);
        ellipse->set_position(pos);
        ellipse->set_radius({ radius.x, radius.y * 0.985 });
        ellipse->set_color(body->get_color());
    }
}

std::shared_ptr<Body> SpaceDemo::spawn_body(const Vec2d position, const Vec2d velocity, const double radius, const double mass, const Color4 color)
{
    return spawn_body("", position, velocity, radius, mass, color);
}

std::shared_ptr<Body> SpaceDemo::spawn_body(const std::string name, const Vec2d position, const Vec2d velocity, const double radius, const double mass, const Color4 color)
{
    return spawn_body(name, position, velocity, radius, mass, false, color);
}

std::shared_ptr<Body> SpaceDemo::spawn_body(const std::string name, const Vec2d position, const Vec2d velocity, const double radius, const double mass, const bool locked, const Color4 color)
{
    auto circle = std::make_shared<Ellipse2D>();
    circle->set_filled(true);
    circle->set_anchor({ 0.5, 0.5 });
    renderer->add_item(circle);

    RenderBody render_body { circle, nullptr };

    auto body = std::make_shared<Body>(name, position, velocity, radius, mass, locked, color);

    body_items.emplace(std::make_pair(body, render_body));
    body_list.push_back(body);
    return body_items.begin()->first;
}

void SpaceDemo::clear_bodies()
{
    body_items.clear();
    body_list.clear();
    renderer->clear_items();
}

void SpaceDemo::handle_input(const int input)
{
    camera.handle_input(input);

    switch (input)
    {
        case ' ':
            scroll_zoom_in = !scroll_zoom_in;
            break;

        case 'c':
            clear_bodies();
            break;

        case 'K':
            time_scale *= 1.5;
            break;

        case 'J':
            time_scale /= 1.5;
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

void SpaceDemo::report_mouse(const demos::common::core::MouseEvent event)
{
    mouse_pos = event.position;
    hover_mouse = true;
    switch (event.type)
    {
        case MouseEventType::LEFT_DOWN:
            {
                if (hovered_body)
                {
                    track_body(hovered_body);
                }
                break;
            }

        case MouseEventType::SCROLL_UP:
            if (scroll_zoom_in)
            {
                camera.smooth_zoom(0.9);
            }
            else
            {
                camera.smooth_zoom(1.1);
            }
            break;

        case MouseEventType::SCROLL_DOWN:
            zoom(1.1);
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

void SpaceDemo::update_hovered_brackets(const double time_lerp)
{
    if (hovered_body == nullptr)
    {
        left_bracket->set_visible(false);
        right_bracket->set_visible(false);
        return;
    }
    left_bracket->set_visible(true);
    right_bracket->set_visible(true);

    auto body { hovered_body };

    double body_screen_radius { 
        units::metres_to_pixels(body->get_radius(), view_bounds.size(), get_resolution()).x 
    };

    Vec2d pos { get_screen_pos(body_interpolated_pos(body, time_lerp)) };

    double offset { 
        std::max(body_screen_radius * 3.0, min_bracket_distance) +
        1 + std::sin(t_sec * std::numbers::pi * 2.0 * bracket_frequency) * bracket_amplitude
    };

    left_bracket->set_position(pos - Vec2d { offset, 0 });
    right_bracket->set_position(pos + Vec2d { offset, 0 });

    double scale { 
        std::lerp(
            0.0, 
            std::max(body_screen_radius * 2.5, min_bracket_scale) / 100, 
            hovered_time
        ) 
    };

    left_bracket->set_scale(scale);
    right_bracket->set_scale(scale);

    double thickness { 
        std::clamp(body_screen_radius / 3, min_bracket_thickness, max_bracket_thickness) 
    };
    left_bracket->set_line_thickness(thickness / left_bracket->get_scale().x);
    right_bracket->set_line_thickness(thickness / right_bracket->get_scale().x);
}

std::shared_ptr<Body> SpaceDemo::get_tracked_body()
{
    if (tracked_body_index < 0 || tracked_body_index >= body_list.size())
    {
        return nullptr;
    }
    return body_list[tracked_body_index];
}

std::shared_ptr<Body> SpaceDemo::get_closest_body(const Vec2d position, const double max_distance)
{
    std::shared_ptr<Body> closest_body { nullptr };
    double closest_distance { std::numeric_limits<double>::max() };

    for (auto body : body_list)
    {
        double distance = Vec2d::distance(position, body->get_position());
        if (distance < closest_distance)
        {
            closest_distance = distance;
            closest_body = body;
        }
    }
    return (max_distance == 0 || closest_distance <= max_distance) ? closest_body : nullptr;
}

std::shared_ptr<Body> SpaceDemo::get_closest_body_screenspace(const Vec2d screen_pos, const double max_distance, const double euqality_threshold, const double time_lerp)
{
    std::shared_ptr<Body> closest_body { nullptr };
    double closest_distance { std::numeric_limits<double>::max() };

    for (auto body : body_list)
    {
        Vec2d pos { get_screen_pos(body_interpolated_pos(body, time_lerp)) };
        double distance { 
            Vec2d::distance(screen_pos, pos) -  
            units::metres_to_pixels(body->get_radius(), view_bounds.size(), get_resolution()).x
        };
        if (distance < closest_distance)
        {
            bool equal { std::abs(distance - closest_distance) < euqality_threshold };
            if (equal && body->get_radius() < closest_body->get_radius())
            {
                continue;
            }
            closest_distance = distance;
            closest_body = body;
        }
    }
    return (max_distance == 0 || closest_distance <= max_distance) ? closest_body : nullptr;
}

Vec2d SpaceDemo::body_interpolated_pos(const std::shared_ptr<Body> body, const double time_lerp)
{
    RenderBody render_body { body_items.at(body) };
    return (Vec2d::lerp(
        render_body.previous_pos, 
        body->get_position(), 
        time_lerp
    ));
}

void SpaceDemo::cycle_tracked_body(const int direction)
{
    auto body { body_list[((tracked_body_index + direction) % body_list.size())] };
    track_body(body);
}

void SpaceDemo::track_body(const std::shared_ptr<Body> body)
{
    camera.size0 = view_bounds.size();
    camera.start_pos = get_anchor_world_pos();
    camera.size_cur = view_bounds.size();
    camera.cur_pos = get_anchor_world_pos();

    previous_tracked_body = camera.state == Camera::State::Tracking ? 
        get_tracked_body() : nullptr;

    for (int i = 0; i < body_list.size(); ++i)
    {
        if (body_list[i] == body)
        {
            tracked_body_index = i;
        }
    }

    camera.zoom_out_size = std::max(
        get_tracked_body()->get_radius() * tracked_body_zoom_level,
        Vec2d::distance(camera.start_pos, get_tracked_body()->get_position()) * 4.0
    );

    camera.size1 = get_tracked_body()->get_radius() * tracked_body_zoom_level;
    camera.end_pos = get_tracked_body()->get_position();
    camera.state = Camera::State::Transitioning;
    camera.velocity = { 0.0, 0.0 };
    camera.zoom_velocity = 0.0;
    camera.track_time = 0.0;
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
