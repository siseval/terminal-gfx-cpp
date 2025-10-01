#ifndef SPACE_DEMO_H
#define SPACE_DEMO_H

#include <unordered_map>
#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>
#include <demos/common/animations/space/body.h>
#include <demos/common/animations/space/planet.h>

namespace demos::common::animations::space
{

class SpaceDemo : public demos::common::core::GfxDemo
{

public:

    SpaceDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer) : 
        GfxDemo(renderer), 
        body_items(std::unordered_map<std::shared_ptr<Body>, std::shared_ptr<gfx::primitives::Ellipse2D>>()) {}


    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const char input) override;

    std::vector<std::string> debug_text() override
    {
        return { 
            "tracked body: " + (get_tracked_body() ? get_tracked_body()->get_name() : "none"),
            "world_pos:" + std::to_string(get_anchor_world_pos().x) + ", " + std::to_string(get_anchor_world_pos().y),
        };
    }

    std::shared_ptr<Body> spawn_body(const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const double radius, const double mass, const gfx::core::types::Color4 color);
    std::shared_ptr<Body> spawn_body(const std::string name, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const double radius, const double mass, const gfx::core::types::Color4 color);
    void clear_bodies();

    void physics_process(const double dt);
    void process_bodies(const double dt);
    void update_view(const double dt);

    void smooth_pan(const gfx::math::Vec2d direction);
    void smooth_zoom(const double factor);

    void update_render_items();

    void set_view_pos(const gfx::math::Vec2d pos);
    void set_view_size(const double width);

    void zoom(const double factor);

    gfx::math::Vec2d get_screen_pos(const gfx::math::Vec2d world_pos);
    gfx::math::Vec2d get_world_pos(const gfx::math::Vec2d screen_pos);

    inline gfx::math::Box2d get_view_bounds() const { return view_bounds; }

    inline gfx::math::Vec2d get_anchor_world_pos() { return view_bounds.min + view_bounds.size() * view_anchor; }
    inline gfx::math::Vec2d get_anchor_screen_pos() { return view_bounds.size() * view_anchor; }

    std::shared_ptr<Body> get_tracked_body();
    void cycle_tracked_body(const int direction = 1);
    void untrack_body();

private: 

    std::unordered_map<std::shared_ptr<Body>, std::shared_ptr<gfx::primitives::Ellipse2D>> body_items;
    std::vector<std::shared_ptr<Body>> body_list;

    int tracked_body_index = -1;

    double pan_speed { 0.1 };
    double track_speed { 40.0 };
    gfx::math::Vec2d camera_velocity { 0.0, 0.0 };
    double zoom_velocity { 0 };

    gfx::math::Box2d view_bounds;
    gfx::math::Vec2d view_anchor { 0.5, 0.5 };
    double simulation_time = 0.0;
    double time_scale = 1.0;

};

}

#endif // SPACE_DEMO_H
