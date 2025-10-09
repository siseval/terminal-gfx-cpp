#ifndef SNAKE_DEMO_H
#define SNAKE_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>

namespace demos::common::animations::snake
{

class SnakeDemo : public demos::common::core::GfxDemo
{

public:

    SnakeDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer) {}

    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const int input) override;
    void report_mouse(const demos::common::core::MouseEvent event) override {}

    virtual std::vector<std::string> debug_text() override
    {
        return { "dt: " + std::to_string(last_frame_us / CLOCKS_PER_SEC) };
    }

private:

    void move_target(const double dt);
    void move_head(const double dt);
    void move_segments();

    void die();
    void do_dead(const double dt);

    void remove_food();
    void add_food();
    gfx::math::Vec2d closest_food();

    void update_segments();
    void add_segment();
    void remove_segment();
    void update_scale(const double s);

    bool control = false;
    bool dead = true;
    double explode_speed = 100;
    double dead_time = 0.0;

    bool first_init = true;

    int num_segments = 64;
    double scale = 1.0;

    double segment_length = 2.0;
    double segment_width = 1.0;
    double segment_spacing = 1.0;

    gfx::math::Vec2d head_target;
    gfx::math::Vec2d head_dir;
    gfx::math::Vec2d head_dimensions { 5, 2.5 };

    double speed = 30;
    double turn_speed = 5;

    double target_speed = 30;
    gfx::math::Vec2d target_direction;
    gfx::math::Vec2d target_bounds_margin;
    bool target_visible = false;

    double food_radius = 0.5;
    std::vector<std::shared_ptr<gfx::primitives::Circle2D>> food;

    std::shared_ptr<gfx::primitives::Polyline2D> tongue;
    std::shared_ptr<gfx::primitives::Polyline2D> head;
    std::vector<std::shared_ptr<gfx::primitives::Ellipse2D>> segments;
    std::shared_ptr<gfx::primitives::Circle2D> target_marker;

};

}

#endif // SNAKE_DEMO_H
