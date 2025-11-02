#ifndef FRACTAL_DEMO_H
#define FRACTAL_DEMO_H

#include <gfx/core/render-2D.h>
#include <gfx/primitives/bitmap-2D.h>
#include <demos/common/core/gfx-demo.h>
#include <gfx/math/vec2.h>
#include <gfx/math/box2.h>
#include <demos/common/animations/fractal/fractal.h>
#include <demos/common/animations/fractal/mandelbrot.h>
#include <demos/common/animations/fractal/julia.h>

namespace demos::common::animations::fractal
{

class FractalDemo : public demos::common::core::GfxDemo
{

public:

    FractalDemo(const std::shared_ptr<gfx::core::Render2D> renderer)
        : GfxDemo(renderer) {}

    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const int input) override;
    void report_mouse(const demos::common::core::MouseEvent event) override;

    std::vector<std::string> debug_text() override
    {
        return { 
            "view: [" + std::to_string(view.min.x) + ", " + std::to_string(view.min.y) + "] - [" + std::to_string(view.max.x) + ", " + std::to_string(view.max.y) + "]",
            "cursor: [" + std::to_string(cursor_pos.x) + ", " + std::to_string(cursor_pos.y) + "]",
            "a: " + std::to_string(a) + " (freq: " + std::to_string(a_frequency) + ")",
            "constant: " + std::to_string(fractal.constant.real()) + " + " + std::to_string(fractal.constant.imag()) + "i",
        };
    }

private:

    bool is_inside_cardioid_or_bulb(double re, double im);
    void zoom(const double factor);
    void pan(const gfx::math::Vec2d acceleration);
    void set_a_frequency(const double freq);
    void update_view(const double dt);
    void handle_mouse_pan(const double dt);
    inline gfx::math::Vec2d screen_to_world(const gfx::math::Vec2d pos)
    {
        gfx::math::Vec2d resolution { renderer->get_resolution() };
        return {
            view.min.x + (static_cast<double>(cursor_pos.x) / resolution.x) * (view.max.x - view.min.x),
            view.min.y + (static_cast<double>(cursor_pos.y) / resolution.y) * (view.max.y - view.min.y)
        };
    }

    Julia fractal;
    std::shared_ptr<gfx::primitives::Bitmap2D> bitmap;
    gfx::math::Box2d view { { -2.0, -1.0 }, { 1.0, 1.0 } };
    double a { 0 };
    double a_frequency { 0.01 };
    bool paused { false };

    int num_colors { 1000 };
    std::vector<gfx::core::types::Color4> colors;
    gfx::core::types::Color4 color0 { 0, 50, 255 };
    gfx::core::types::Color4 color1 { 255, 255, 150 };
    gfx::core::types::Color4 color2 { 255, 255, 255 };

    gfx::math::Vec2d cursor_pos { 0, 0 };
    double mouse_pan_sensitivity { 0.001 };

    gfx::math::Vec2d pan_velocity { 0, 0 };
    double mouse_pan_threshold { 0.4 };
    double zoom_velocity { 0.0 };

    double max_pan_velocity { 10.0 };
    double max_zoom_velocity { 10.0 };

    double zoom_factor { 1.5 };
    double pan_factor { 0.3 };

};

}

#endif // FRACTAL_DEMO_H
