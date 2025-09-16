#include <gfx/core/gfx-render-2D.h>

namespace gfx::core
{

using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;


void GfxRender2D::draw_frame() const
{
    surface->clear_frame_buffer();

    primitives->sort_by_depth();
    for (auto primitive : primitives->get_items())
    {
        Matrix3x3d global_transform = get_global_transform() * primitive->get_transform();
        primitive->rasterize(surface, global_transform);
        // if (primitive->get_draw_bounds())
        // {
        //     primitive->rasterize_bounds(surface);
        // }
        // if (primitive->get_draw_anchor())
        // {
        //     primitive->rasterize_anchor(surface);
        // }
    }

    surface->write_pixel(Vec2i { 2, 2 }, Color3 { 255, 0, 0 });
    surface->present();
}

gfx::math::Matrix3x3d GfxRender2D::get_global_transform() const
{
    Matrix3x3d scale = utils::scale(viewport_scaling);
    return scale;
}

std::shared_ptr<Ellipse2D> GfxRender2D::create_ellipse(const Vec2d position, const Vec2d radius, const Color3 color, const double line_thickness) const
{
    auto ellipse = std::make_shared<Ellipse2D>();

    ellipse->set_pos(position);
    ellipse->set_radius(radius);
    ellipse->set_line_thickness(line_thickness);
    ellipse->set_color(color);

    return ellipse;
}

std::shared_ptr<Polyline2D> GfxRender2D::create_polyline(const Vec2d position, const std::vector<Vec2d> points, const Color3 color, const double line_thickness) const
{
    auto polyline = std::make_shared<Polyline2D>();

    polyline->set_pos(position);
    polyline->set_points(points);
    polyline->set_line_thickness(line_thickness);
    polyline->set_color(color);

    return polyline;
}

}
