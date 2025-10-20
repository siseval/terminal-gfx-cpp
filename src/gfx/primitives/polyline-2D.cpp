#include <numbers>
#include <gfx/primitives/polyline-2D.h>
#include <gfx/utils/transform.h>
#include <gfx/geometry/triangulate.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;
using namespace gfx::geometry;


Box2d Polyline2D::get_geometry_size() const
{
    Box2d bounds { Vec2d::zero(), Vec2d::zero() };

    for (auto point : points)
    {
        bounds.expand(point);
    }

    return bounds;
}

Box2d Polyline2D::get_axis_aligned_bounding_box(const Matrix3x3d &transform) const
{
    Box2d extent { get_geometry_size() };
    Vec2d line_extent { std::ceil(line_thickness / 2.0), std::ceil(line_thickness / 2.0) };
    Vec2d top_left { extent.min - line_extent };
    Vec2d bot_right { extent.max + line_extent };

    std::vector<Vec2d> corners {
        { top_left.x, top_left.y },
        { bot_right.x, top_left.y },
        { top_left.x, bot_right.y },
        { bot_right.x, bot_right.y },
    };
    std::vector<Vec2d> transformed_corners { utils::transform_points(corners, transform) };

    Box2d bounds { transformed_corners[0], transformed_corners[0] };
    bounds.expand(transformed_corners);

    return bounds;
}


bool Polyline2D::point_collides(const Vec2d point, const Matrix3x3d &transform) const
{
    return false;
}

void Polyline2D::rasterize_filled_triangle(std::shared_ptr<RenderSurface> surface, const Triangle &triangle) const
{
    Box2d bounds {
        { 
            std::min({triangle.v0.x,triangle.v1.x,triangle.v2.x }), 
            std::min({triangle.v0.y,triangle.v1.y,triangle.v2.y }) 
        },
        { 
            std::max({triangle.v0.x,triangle.v1.x,triangle.v2.x }), 
            std::max({triangle.v0.y,triangle.v1.y,triangle.v2.y }) 
        }
    };

    for (int y = bounds.min.y; y <= bounds.max.y; y++)
    {
        for (int x = bounds.min.x; x <= bounds.max.x; x++)
        {
            Vec2d pos { static_cast<double>(x), static_cast<double>(y) };

            if (triangle.point_inside(pos))
            {
                surface->write_pixel(pos.round(), get_color(), get_depth());
            }
        }
    }
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
        rasterize_filled_triangle(surface, { transformed_pos, vertices[i], vertices[i + 1] });
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

    rasterize_filled_triangle(surface, { v0, v1, v2 });
    rasterize_filled_triangle(surface, { v1, v3, v2 });
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
            rasterize_filled_triangle(surface, { transformed_points[0], transformed_points[1], transformed_points[2] });
        }
        else
        {
            std::vector<Triangle> triangles { geometry::triangulate_polygon(transformed_points, clockwise) };
            for (auto triangle : triangles)
            {
                rasterize_filled_triangle(surface, triangle);
            }
        }
    }

    if (do_rounded_corners)
    {
        rasterize_rounded_corners(surface, transform);
    }
}

bool Polyline2D::cache_clockwise()
{
    double sum = 0.0;
    for (int i = 0; i < points.size(); ++i)
    {
        Vec2d p0 { points[i] };
        Vec2d p1 { points[(i + 1) % points.size()] };
        sum += (p1.x - p0.x) * (p1.y + p0.y);
    }
    clockwise = sum < 0.0;
    return clockwise;
}


}
