#include <common/animations/snake-demo.h>

namespace demos::common::animations
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;


void SnakeDemo::init()
{
    Vec2d resolution = get_resolution();
    Vec2d center = resolution / 2;

    renderer->clear_items();
    renderer->get_render_surface()->clear_palette();
    segments.clear();

    std::vector<Vec2d> head_points = {
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

    for (int i = 0; i < num_segments; i++)
    {
        add_segment();
    }

    target_marker = renderer->create_circle(head_target, 1.0, Color4(1.0, 0.0, 0.0, 1.0), 1.0);
    target_marker->set_fill(true);
    renderer->add_item(target_marker);
}

void SnakeDemo::move_target(const double dt)
{
    head_target += target_direction * target_speed  * dt;
    target_direction += Vec2d {
        (static_cast<double>(rand()) / RAND_MAX - 0.5) * 0.1, 
        (static_cast<double>(rand()) / RAND_MAX - 0.5) * 0.1
    };
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
    Vec2d goal = food.empty() ? head_target : closest_food();

    Vec2d to_target = (goal - head->get_pos()).normalize();

    head->set_rotation(Vec2d::from_angle(head->get_rotation()).rotate_towards(to_target, turn_speed * dt).angle());
    head->set_pos(head->get_pos() + Vec2d::from_angle(head->get_rotation(), speed * dt));

    for (int i = 0; i < food.size(); i++)
    {
        if (Vec2d::distance(head->get_pos(), food[i]->get_pos()) < segment_length * 0.8)
        {
            renderer->remove_item(food[i]);
            food.erase(food.begin() + i);
        }
    }
}

void SnakeDemo::move_segments()
{
    segments[0]->set_pos(head->get_pos() - Vec2d::from_angle(head->get_rotation(), segment_spacing));
    segments[0]->set_rotation(head->get_rotation());
    for (int i = 1; i < num_segments; i++)
    {
        Vec2d direction = segments[i - 1]->get_pos() - segments[i]->get_pos();
        segments[i]->set_rotation(direction.angle());
        segments[i]->set_pos(segments[i - 1]->get_pos() - Vec2d::from_angle(segments[i]->get_rotation(), segment_spacing * scale));
    }
}

void SnakeDemo::render_frame()
{
    double t0 = static_cast<double>(clock());
    delta_time = last_frame_time / CLOCKS_PER_SEC;

    move_target(delta_time);
    move_head(delta_time);
    move_segments();

    renderer->draw_frame();
    last_frame_time = static_cast<double>(clock()) - t0;
}

Vec2d SnakeDemo::closest_food()
{
    double closest_dist = Vec2d::distance(head->get_pos(), food[0]->get_pos());
    Vec2d closest_pos = food[0]->get_pos();
    for (int i = 1; i < food.size(); i++)
    {
        double dist = Vec2d::distance(head->get_pos(), food[i]->get_pos());
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
    for (int i = 0; i < segments.size(); i++)
    {
        double progress = static_cast<double>(i) / num_segments;

        Vec2d radius = { 
            segment_length * (1.0 - progress * 0.5), 
            segment_spacing * (1.0 - progress * 0.5) 
        };
        Color4 color = Color4(0.0, 1.0, progress, 1.0);
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
    Vec2d pos = { 
        target_bounds_margin.x + static_cast<double>(rand()) / RAND_MAX * (get_resolution().x - target_bounds_margin.x * 2),
        target_bounds_margin.y + static_cast<double>(rand()) / RAND_MAX * (get_resolution().y - target_bounds_margin.y * 2)
    };
    food.push_back(renderer->create_circle(pos, food_radius, Color4(1.0, 0.7, 0.0, 1.0), 1.0));
    food.back()->set_fill(true);
    renderer->add_item(food.back());
}

void SnakeDemo::add_segment()
{
    auto segment = renderer->create_ellipse({ 0, 0 }, { 0, 0 }, Color4(0, 0, 0));
    segment->set_fill(true);
    segment->set_anchor({ 0.5, 0.5 });
    if (!segments.empty())
    {
        segment->set_pos(segments.back()->get_pos());
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
}

}
