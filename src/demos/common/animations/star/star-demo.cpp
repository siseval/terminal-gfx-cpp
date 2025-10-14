#include <demos/common/animations/star/star-demo.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::star
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;
using namespace demos::common::core;


void StarDemo::init()
{
    Vec2d resolution { get_resolution() };
    Vec2d center { resolution / 2 };
    double distance_ratio = 16;

    renderer->clear_items();
    renderer->get_render_surface()->clear_palette();
    polylines.clear();
    for (int i = 0; i < num_polylines; ++i)
    {
        double progress { static_cast<double>(i) / num_polylines };

        Color4 inner { 1.0, 0.8, 0.1 };
        Color4 outer { 0.9, 0.5, 1.0 };
        Color4 color { Color4::lerp(inner, outer, progress) };

        std::vector<Vec2d> points {
            { 0, -resolution.y / distance_ratio },
            { resolution.x / distance_ratio, 0 },
            { 0, resolution.y / distance_ratio },
            { -resolution.x / distance_ratio, 0 },
        };

        auto polyline { renderer->create_polyline(center, points, color) };
        polyline->set_close(true);
        polyline->set_fill(true);
        polyline->set_rounded_corners(true);
        polyline->set_anchor({ 0.5, 0.5 });

        polylines.push_back(polyline);
        renderer->add_item(polyline);
    }
}

void StarDemo::render_frame(const double dt)
{
    double t0 { utils::time_us() };

    double t { utils::time_ms() * 0.002 * speed };
    double sin_t { std::sin(t) };
    double cos_t { std::cos(t * 2) };

    for (int i = 0; i < num_polylines; ++i)
    {
        double progress { static_cast<double>(i) / num_polylines };
        auto polyline { polylines[i] };

        polyline->set_scale({ 1.0 + progress * (0.8 + sin_t * 0.4), 1.0 + progress * (1 + cos_t * 0.8) });
        polyline->set_rotation(t * (1.0 + progress));
        polyline->set_line_thickness(1 + progress * 1 + (1 + sin_t) * 1);
    }

    renderer->draw_frame();
}

void StarDemo::handle_input(const int input)
{
    switch (input)
    {
        case 'k':
            num_polylines += 1;
            init();
            break;

        case 'j':
            if (num_polylines > 1)
            {
                num_polylines -= 1;
                init();
            }
            break;

        default:
            break;
    }
}

void StarDemo::end()
{
    renderer->clear_items();
    polylines.clear();
}

}
