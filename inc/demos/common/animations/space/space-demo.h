#ifndef SPACE_DEMO_H
#define SPACE_DEMO_H

#include <unordered_map>
#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>
#include <demos/common/animations/space/body.h>
#include <demos/common/animations/space/planet.h>
#include <demos/common/animations/space/camera.h>

namespace demos::common::animations::space
{

class SpaceDemo : public demos::common::core::GfxDemo
{
    struct RenderBody
    {
        std::shared_ptr<gfx::primitives::Ellipse2D> ellipse;
        std::shared_ptr<gfx::primitives::Polyline2D> trail;

        gfx::math::Vec2d previous_pos { 0.0, 0.0 };
    };

public:

    SpaceDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer) : 
        GfxDemo(renderer), 
        body_items(std::unordered_map<std::shared_ptr<Body>, RenderBody>()) {}


    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const int input) override;
    void report_mouse(const demos::common::core::MouseEvent event) override;

    std::vector<std::string> debug_text() override
    {
        std::string state_str = (camera.state == Camera::State::Free ? "Free" : (camera.state == Camera::State::Tracking ? "Tracking" : "Transitioning"));
        gfx::math::Vec2d mouse_world_pos = get_world_pos(mouse_pos);
        return { 
            "tracked body: " + (get_tracked_body() ? get_tracked_body()->get_name() : "none"),
            "world pos:" + std::to_string(get_anchor_world_pos().x) + ", " + std::to_string(get_anchor_world_pos().y),
            "camera state: " + state_str,
            "time scale: " + std::to_string(time_scale) + "x",
            "mouse pos: " + std::to_string(mouse_world_pos.x) + ", " + std::to_string(mouse_world_pos.y),
            std::to_string(camera.size_cur.x) + " x " + std::to_string(camera.size_cur.y) + " units",
        };
    }

    std::shared_ptr<Body> spawn_body(const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const double radius, const double mass, const gfx::core::types::Color4 color);
    std::shared_ptr<Body> spawn_body(const std::string name, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const double radius, const double mass, const gfx::core::types::Color4 color);
    std::shared_ptr<Body> spawn_body(const std::string name, const gfx::math::Vec2d position, const gfx::math::Vec2d velocity, const double radius, const double mass, const bool locked, const gfx::core::types::Color4 color);

    void clear_bodies();

    void physics_process(const double dt);
    void process_bodies(const double dt);
    void handle_camera(const double dt, const double time_lerp);

    void update_render_items(const double time_lerp = 1.0);

    void zoom(const double factor);

    void set_camera_pos(const gfx::math::Vec2d pos) { camera.cur_pos = pos; }
    void set_camera_size(const double size) { camera.size_cur = gfx::math::Vec2d { size, size * get_resolution().y / get_resolution().x }; }

    gfx::math::Vec2d get_screen_pos(const gfx::math::Vec2d world_pos);
    gfx::math::Vec2d get_world_pos(const gfx::math::Vec2d screen_pos);

    inline gfx::math::Box2d get_view_bounds() const { return view_bounds; }

    inline gfx::math::Vec2d get_anchor_world_pos() { return view_bounds.min + view_bounds.size() * view_anchor; }
    inline gfx::math::Vec2d get_anchor_screen_pos() { return view_bounds.size() * view_anchor; }

    std::shared_ptr<Body> get_closest_body(const gfx::math::Vec2d position);
    std::shared_ptr<Body> get_tracked_body();
    void cycle_tracked_body(const int direction = 1);
    void track_body(const std::shared_ptr<Body> body);
    void untrack_body();

private: 

    void set_view_pos(const gfx::math::Vec2d pos);
    void set_view_size(const double width);

    gfx::math::Vec2d predict_orbital_pos(std::shared_ptr<Body> body, const double future_time);
    std::shared_ptr<Body> get_largest_body();

    static constexpr double PHYSICS_TIME_STEP { 0.0001 };
    static constexpr int MAX_STEPS_PER_FRAME { 500 };
    double time_accumulator { 0.0 };

    gfx::math::Vec2d mouse_pos { 0.0, 0.0 };
    bool scroll_zoom_in { true };

    Camera camera;

    std::unordered_map<std::shared_ptr<Body>, RenderBody> body_items;
    std::vector<std::shared_ptr<Body>> body_list;

    int tracked_body_index { -1 };
    std::shared_ptr<Body> previous_tracked_body { nullptr };
    double tracked_body_zoom_level { 20.0 };

    gfx::math::Box2d view_bounds;
    gfx::math::Vec2d view_anchor { 0.5, 0.5 };
    double simulation_time { 0.0 };
    double time_scale { 1.0 };

};

}

#endif // SPACE_DEMO_H
