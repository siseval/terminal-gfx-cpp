#include <common/animations/polyline-demo.h>

namespace demos::common::animations
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;


void PolylineDemo::init()
{
    Vec2d resolution = get_resolution();
    Vec2d center = resolution / 2;
    double distance_ratio = 7;
    double progress;

    for (int i = 0; i < num_polylines; i++)
    {
        progress = static_cast<double>(i) / num_polylines;

        Color4 color = Color4(progress, 0.0, 1 - progress, 1.0);
        std::vector<Vec2d> points = { { 0, 0 }, { 0, resolution.y / distance_ratio }, { resolution.x / distance_ratio } };

        auto polyline = renderer->create_polyline(center, points, color);
        polyline->set_close(true);
        polyline->set_fill(true);
        polyline->set_rounded_corners(true);
        polyline->set_anchor({ 0.5, 0.5 });

        polylines.push_back(polyline);
        renderer->add_item(polyline);
    }
}

void PolylineDemo::render_frame()
{
    double t0 = static_cast<double>(clock());

    double t = static_cast<double>(clock()) * 0.000002 * speed;
    double sin_t = std::sin(t);
    double cos_t = std::cos(t * 2);
    double progress;

    for (int i = 0; i < num_polylines; i++)
    {
        progress = static_cast<double>(i) / num_polylines;
        auto polyline = polylines[i];

        polyline->set_scale(Vec2d { 1.0 + progress * (1.4 + sin_t * 0.8), 1.0 + progress * (1 + cos_t) });
        polyline->set_rotation(t * (1.0 + progress));
        polyline->set_line_thickness(1 + progress * 1 + (1 + sin_t) * 1);
    }

    renderer->draw_frame();
    last_frame_time = static_cast<double>(clock()) - t0;
}

void PolylineDemo::end()
{
    renderer->clear_items();
    polylines.clear();
}

}
