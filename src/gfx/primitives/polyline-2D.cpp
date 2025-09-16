#include <gfx/primitives/polyline-2D.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;


Box2d Polyline2D::get_relative_extent() const
{
    Box2d bounds = { Vec2d::zero(), Vec2d::zero() };

    for (auto point : points)
    {
        bounds.expand(point);
    }

    return bounds;
}

void Polyline2D::rasterize_edge(std::shared_ptr<RenderSurface> surface, const Vec2d start, const Vec2d end, const Matrix3x3d transform) const
{
    double line_extent = line_thickness / 2.0;
    Vec2d normal = (end - start).normal().normalize();

    Vec2d offset = normal * line_extent;

    Vec2d v0 = start + offset;
    Vec2d v1 = start - offset;
    Vec2d v2 = end + offset;
    Vec2d v3 = end - offset;

    v0 = utils::apply_transform(v0, transform);
    v1 = utils::apply_transform(v1, transform);
    v2 = utils::apply_transform(v2, transform);
    v3 = utils::apply_transform(v3, transform);

    utils::rasterize_filled_triangle(surface, v0, v1, v2, color);
    utils::rasterize_filled_triangle(surface, v1, v3, v2, color);
}

void Polyline2D::rasterize(std::shared_ptr<RenderSurface> surface, const Matrix3x3d transform) const
{
    if (points.size() < 2)
    {
        return;
    }

    for (int i = 0; i < points.size() - 1; i++)
    {
        rasterize_edge(surface, points[i], points[i + 1], transform);
    }
    if (do_close)
    {
        rasterize_edge(surface, points.back(), points.front(), transform);
    }
    if (get_fill())
    {
        std::vector<Vec2d> transformed_points = utils::apply_transform(points, transform);
        utils::rasterize_filled_polygon(surface, transformed_points, get_color());
    }
}


}
