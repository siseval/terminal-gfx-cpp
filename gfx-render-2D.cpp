#include "gfx-render-2D.h"

namespace curspp::graphics
{

void GfxRender2D::draw_frame() const
{
    clear_frame_buffer(context);

    primitives->sort_by_depth();
    for (auto primitive : primitives->get_items())
    {
        primitive->rasterize(context);
        if (primitive->get_draw_bounds())
        {
            primitive->rasterize_bounds(context);
        }
        if (primitive->get_draw_anchor())
        {
            primitive->rasterize_anchor(context);
        }
    }

    draw_frame_buffer(context);
}

std::shared_ptr<Ellipse2D> GfxRender2D::create_ellipse(const Vec2d position, const Vec2d radius, const Color3 color, const double line_thickness) const
{
    auto ellipse = std::make_shared<Ellipse2D>();

    ellipse->set_radius(radius);
    ellipse->set_line_thickness(line_thickness);
    ellipse->set_pos(position);
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

void GfxRender2D::write_raster_to_frame_buffer(const std::vector<bool> raster, const BBox2D bounds, const Color3 color)
{
    Box2i rounded_bounds = { bounds.min.round(), bounds.max.round() };
    for (int i = 0; i < rounded_bounds.max.x * rounded_bounds.max.y; i++)
    {
        if (raster[i])
        {
            Vec2i pos = rounded_bounds.min + Vec2i { i % rounded_bounds.max.x, i / rounded_bounds.max.x };
            write_pixel(context, pos, color);
        }
    }
}

}
