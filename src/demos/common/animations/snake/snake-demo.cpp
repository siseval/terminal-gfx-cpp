#include <demos/common/animations/snake/snake-demo.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::snake
{

using namespace demos::common::core;
using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;


void SnakeDemo::init()
{
    Vec2d resolution { get_resolution() };
    Vec2d center { resolution / 2 };

    speed = resolution.x * 0.3;
    target_speed = speed * 1.1;
    explode_speed = speed * 3.0;

    segment_length = resolution.x * 0.02;
    segment_width = segment_length * 0.5;
    segment_spacing = segment_length * 0.5;
    head_dimensions = { segment_length * 2.5, segment_width * 2.5 };
    target_bounds_margin = resolution * 0.1;

    renderer->clear_items();
    renderer->get_render_surface()->clear_palette();
    segments.clear();

    std::vector<Vec2d> head_points {
        { 0, 0 },
        { head_dimensions.x / 2, head_dimensions.y / 2 },
        { head_dimensions.x, 0 },
        { head_dimensions.x / 2, -head_dimensions.y / 2 }
    };

    head_target = center;
    head = renderer->create_polyline(center, head_points, Color4(0.0, 1.0, 0.0, 1.0), 2.0);
    head->set_close(true);
    head->set_fill(true);
    head->set_rounded_corners(true);
    head->set_scale(scale);
    head->set_depth(0);
    renderer->add_item(head);

    std::vector<Vec2d> tongue_points {
        { 0, 0 },
        { head_dimensions.x * 0.2, head_dimensions.y * 0.05 },
        { head_dimensions.x * 0.4, head_dimensions.y * 0.2 },
        { head_dimensions.x * 0.3, 0 },
        { head_dimensions.x * 0.4, -head_dimensions.y * 0.2 },
        { head_dimensions.x * 0.2, -head_dimensions.y * 0.05 },
    };
    tongue = renderer->create_polyline({ head_dimensions.x, 0 }, tongue_points, Color4(1.0, 0.0, 0.0, 1.0), 0.5);
    tongue->set_close(true);
    tongue->set_fill(true);
    tongue->set_rounded_corners(true);
    tongue->set_depth(1);
    renderer->add_item(tongue, head);

    for (int i = 0; i < num_segments; ++i)
    {
        add_segment();
    }

    target_marker = renderer->create_circle(head_target, 1.0, Color4(1.0, 0.0, 0.0, 1.0), 1.0);
    target_marker->set_fill(true);
    renderer->add_item(target_marker);

    dead = false;
}

void SnakeDemo::move_target(const double dt)
{
    head_target += target_direction * target_speed  * dt;

    if (!control)
    {
        target_direction += Vec2d { utils::random_double(-0.1, 0.1), utils::random_double(-0.1, 0.1) };
    }
    target_direction = target_direction.normalize();
    if (head_target.x < target_bounds_margin.x || 
        head_target.x > get_resolution().x - target_bounds_margin.x)
    {
        target_direction.x = -target_direction.x;
    }
    if (head_target.y < target_bounds_margin.y || 
        head_target.y > get_resolution().y - target_bounds_margin.y)
    {
        target_direction.y = -target_direction.y;
    }
    target_marker->set_pos(head_target);
    target_marker->set_visible(target_visible);
}

void SnakeDemo::move_head(const double dt)
{
    Vec2d goal { food.empty() ? head_target : closest_food() };

    Vec2d to_target { (goal - head->get_pos()).normalize() };

    head->set_rotation(Vec2d::from_angle(head->get_rotation()).rotate_towards(to_target, turn_speed * dt).angle());
    head->set_pos(head->get_pos() + Vec2d::from_angle(head->get_rotation(), speed * dt));

    for (int i = 0; i < food.size(); ++i)
    {
        if (Vec2d::distance(head->get_pos(), food[i]->get_pos()) < segment_length * 0.8)
        {
            renderer->remove_item(food[i]);
            food.erase(food.begin() + i);
            update_scale(scale + 0.02);
            add_segment();
            num_segments += 1;
        }
    }
}

void SnakeDemo::move_segments()
{
    segments[0]->set_pos(head->get_pos() - Vec2d::from_angle(head->get_rotation(), segment_spacing));
    segments[0]->set_rotation(head->get_rotation());
    for (int i = 1; i < num_segments; ++i)
    {
        Vec2d direction { segments[i - 1]->get_pos() - segments[i]->get_pos() };
        segments[i]->set_rotation(direction.angle());
        segments[i]->set_pos(segments[i - 1]->get_pos() - Vec2d::from_angle(segments[i]->get_rotation(), segment_spacing * scale));
    }
}

void SnakeDemo::die()
{
    dead_time = 0.0;
    head->set_rotation_degrees(Vec2d::from_angle(std::rand() % 360).angle_degrees());
    for (int i = 0; i < segments.size(); ++i)
    {
        segments[i]->set_rotation_degrees(Vec2d::from_angle(std::rand() % 360).angle_degrees());
    }
    dead = true;
}

void SnakeDemo::do_dead(const double dt)
{
    head->set_pos(head->get_pos() + Vec2d::from_angle(head->get_rotation(), explode_speed * dt));
    head->set_scale(Vec2d::lerp(Vec2d(scale), { 0.001, 0.001 }, dead_time * 3));
    if (head->get_scale().x <= 0.01)
    {
        head->set_visible(false);
    }
    for (int i = 0; i < segments.size(); ++i)
    {
        segments[i]->set_pos(segments[i]->get_pos() + Vec2d::from_angle(segments[i]->get_rotation(), explode_speed * dt));
        segments[i]->set_scale(Vec2d::lerp(Vec2d(scale), { 0.001, 0.001 }, dead_time * 3));
        if (segments[i]->get_scale().x <= 0.01)
        {
            segments[i]->set_visible(false);
        }
    }
    dead_time += dt;
}

void SnakeDemo::render_frame()
{
    double t0 { utils::time_us() };
    double time_ms { t0 / 1000.0 };
    double dt_sec { delta_us / 1000000 };

    tongue->set_scale(std::sin(std::sin(time_ms / 1000) * 8));
    if (dead)
    {
        do_dead(dt_sec);
    }
    else 
    {
        move_target(dt_sec);
        move_head(dt_sec);
        move_segments();
    }

    renderer->draw_frame();
    delta_us = utils::time_us() - t0;
}

Vec2d SnakeDemo::closest_food()
{
    double closest_dist { Vec2d::distance(head->get_pos(), food[0]->get_pos()) };
    Vec2d closest_pos { food[0]->get_pos() };
    for (int i = 1; i < food.size(); ++i)
    {
        double dist { Vec2d::distance(head->get_pos(), food[i]->get_pos()) };
        if (dist < closest_dist)
        {
            closest_dist = dist;
            closest_pos = food[i]->get_pos();
        }
    }
    return closest_pos;
}

void SnakeDemo::update_segments()
{
    renderer->get_render_surface()->clear_palette();
    for (int i = 0; i < segments.size(); ++i)
    {
        double progress { static_cast<double>(i) / num_segments };

        Vec2d radius { Vec2d::lerp({ segment_length, segment_width }, { 0.1, 0.1 }, progress) };
        Color4 color { Color4::lerp({ 0.0, 1.0, 0.0 }, { 0.0, 1.0, 1.0 }, progress) };
        segments[i]->set_radius(radius);
        segments[i]->set_color(color);
        segments[i]->set_depth(i + 1);
    }
}

void SnakeDemo::remove_food()
{
    if (food.empty()) 
    {
        return; 
    }

    renderer->remove_item(food.back());
    food.pop_back();
}

void SnakeDemo::add_food()
{
    Vec2i pos { 
        utils::random_int(target_bounds_margin.x, get_resolution().x - target_bounds_margin.x),
        utils::random_int(target_bounds_margin.y, get_resolution().y - target_bounds_margin.y)
    };
    food.push_back(renderer->create_circle(pos, food_radius, Color4(1.0, 0.7, 0.0, 1.0), 1.0));
    food.back()->set_fill(true);
    renderer->add_item(food.back());
}

void SnakeDemo::add_segment()
{
    auto segment { renderer->create_ellipse({ 0, 0 }, { 0, 0 }, Color4(0, 0, 0)) };
    segment->set_fill(true);
    segment->set_anchor({ 0.5, 0.5 });
    if (!segments.empty())
    {
        Vec2d pos { dead ? static_cast<Vec2d>(renderer->get_resolution() / 2.0) : segments.back()->get_pos() };
        segment->set_pos(pos);
        segment->set_rotation(segments.back()->get_rotation());
    }
    segment->set_scale(scale);

    update_segments();

    segments.push_back(segment);
    renderer->add_item(segment);
}

void SnakeDemo::remove_segment()
{
    if (segments.empty()) 
    {
        return;
    }

    renderer->remove_item(segments.back());
    segments.pop_back();

    update_segments();
}

void SnakeDemo::update_scale(const double s)
{
    for (auto &segment : segments)
    {
        segment->set_scale(s);
    }
    head->set_scale(s);
    scale = s;
}

void SnakeDemo::handle_input(const char input)
{
    switch (input)
    {
        case 'k':
            add_segment();
            num_segments += 1;
            break;

        case 'j':
            if (num_segments > 1)
            {
                remove_segment();
                num_segments -= 1;
            }
            break;
        case 'l':
            update_scale(scale + 0.1);
            break;
        case 'h':
            if (scale > 0.2)
            {
                update_scale(scale - 0.1);
            }
            break;

        case 'w':
            target_direction = { 0, -1 };
            break;
        case 's':
            target_direction = { 0, 1 };
            break;
        case 'a':
            target_direction = { -1, 0 };
            break;
        case 'd':
            target_direction = { 1, 0 };
            break;

        case 'm':
            if (dead)
            {
                init();
                break;
            }
            die();
            break;

        case 'c':
            control = !control;
            break;

        case 'f':
            add_food();
            break;
        case 'r':
            remove_food();
            break;

        case 'v':
            target_visible = !target_visible;
            break;

        default:
            break;
    }
}

void SnakeDemo::end()
{
    renderer->clear_items();
    dead = true;
}

}
