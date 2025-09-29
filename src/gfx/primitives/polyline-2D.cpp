#include <numbers>
#include <gfx/primitives/polyline-2D.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;


Box2d Polyline2D::get_relative_extent() const
{
    Box2d bounds { Vec2d::zero(), Vec2d::zero() };

    for (auto point : points)
    {
        bounds.expand(point);
    }

    return bounds;
}

void Polyline2D::rasterize_rounded_corner(std::shared_ptr<RenderSurface> surface, const Vec2d pos, const double angle0, const double angle1, const Matrix3x3d &transform) const
{
    std::vector<Vec2d> vertices;

    for (int i = 0; i <= CORNER_SEGMENTS; ++i)
    {
        double progress { static_cast<double>(i) / static_cast<double>(CORNER_SEGMENTS) };
        double theta { angle0 + (angle1 - angle0) * progress };

        Vec2d vertex {
            pos.x + (line_thickness / 2.0) * std::cos(theta),
            pos.y + (line_thickness / 2.0) * std::sin(theta)
        };

        vertices.push_back(utils::transform_point(vertex, transform));
    }
    Vec2d transformed_pos = utils::transform_point(pos, transform);

    for (int i = 0; i < vertices.size() - 1; ++i)
    {
        utils::rasterize_filled_triangle(surface, { transformed_pos, vertices[i], vertices[i + 1] }, color);
    }
}

void Polyline2D::rasterize_rounded_corners(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
{
    for (int i = 0; i < points.size(); ++i)
    {
        Vec2d p0 { points[(i - 1 + points.size()) % points.size()] };
        Vec2d p1 { points[i] };
        Vec2d p2 { points[(i + 1) % points.size()] };

        Vec2d normal0 { (p0 - p1).normal().normalize() };
        Vec2d normal1 { (p1 - p2).normal().normalize() };

        Vec2d between { ((p1 - p0) + (p1 - p2)).normalize() };

        double angle0 { std::atan2(normal0.y, normal0.x) };
        double angle1 { std::atan2(normal1.y, normal1.x) };

        double angle_diff { angle1 - angle0 };
        if (angle_diff <= 0) 
        {
            angle_diff += 2 * std::numbers::pi;
        }

        double angle_overlap = 0.1;
        double pos_overlap = 0.2;

        rasterize_rounded_corner(surface, p1 - between * pos_overlap, angle0 - angle_overlap, angle0 + angle_diff + angle_overlap, transform);
    }
}

void Polyline2D::rasterize_edge(std::shared_ptr<RenderSurface> surface, const Vec2d start, const Vec2d end, const Matrix3x3d &transform) const
{
    double line_extent { line_thickness / 2.0 };
    Vec2d normal { (end - start).normal().normalize() };

    Vec2d offset { normal * line_extent };

    Vec2d v0 { start + offset };
    Vec2d v1 { start - offset };
    Vec2d v2 { end + offset };
    Vec2d v3 { end - offset };

    v0 = utils::transform_point(v0, transform);
    v1 = utils::transform_point(v1, transform);
    v2 = utils::transform_point(v2, transform);
    v3 = utils::transform_point(v3, transform);

    utils::rasterize_filled_triangle(surface, { v0, v1, v2 }, color);
    utils::rasterize_filled_triangle(surface, { v1, v3, v2 }, color);
}

void Polyline2D::rasterize(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
{
    if (points.size() < 2)
    {
        return;
    }

    for (int i = 0; i < points.size() - 1; ++i)
    {
        rasterize_edge(surface, points[i], points[i + 1], transform);
    }
    if (do_close)
    {
        rasterize_edge(surface, points.back(), points.front(), transform);
    }

    if (get_fill())
    {
        std::vector<Vec2d> transformed_points { utils::transform_points(points, transform) };
        if (points.size() == 3)
        {
            utils::rasterize_filled_triangle(surface, { transformed_points[0], transformed_points[1], transformed_points[2] }, get_color());
        }
        else 
        {
            utils::rasterize_filled_polygon(surface, transformed_points, get_color(), clockwise_cached);
        }
    }

    if (do_rounded_corners)
    {
        rasterize_rounded_corners(surface, transform);
    }
}

bool Polyline2D::is_clockwise()
{
    double sum = 0.0;
    for (int i = 0; i < points.size(); ++i)
    {
        Vec2d p0 { points[i] };
        Vec2d p1 { points[(i + 1) % points.size()] };
        sum += (p1.x - p0.x) * (p1.y + p0.y);
    }
    clockwise_cached = sum < 0.0;
    return clockwise_cached;
}


}
