#include <gfx/primitives/polygon-2D.h>
#include <gfx/utils/transform.h>
#include <gfx/geometry/triangulate.h>
#include <gfx/geometry/rasterize.h>


namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;
using namespace gfx::geometry;


Box2d Polygon2D::get_geometry_size() const
{
    Box2d bounds { Vec2d::zero(), Vec2d::zero() };

    for (auto point : points)
    {
        bounds.expand(point);
    }

    return bounds;
}

bool Polygon2D::point_collides(const Vec2d point, const Matrix3x3d &transform) const
{
    Matrix3x3d inverse_transform { utils::invert_affine(transform) };
    Vec2d local_point { utils::transform_point(point, inverse_transform) };

    std::vector<Vec2d> transformed_points { 
        utils::transform_points(points, transform) 
    };

    std::vector<Triangle> triangles { 
        geometry::triangulate_polygon(transformed_points, clockwise) 
    };

    for (auto triangle : triangles)
    {
        if (triangle.point_inside(local_point))
        {
            return true;
        }
    }

    return false;
}

void Polygon2D::rasterize(const Matrix3x3d &transform, const std::function<void(const Pixel&)> emit_pixel) const
{
    if (points.size() < 2)
    {
        return;
    }

    std::vector<Vec2d> transformed_points { 
        utils::transform_points(points, transform) 
    };

    std::vector<Triangle> triangles { 
        geometry::triangulate_polygon(transformed_points, clockwise) 
    };

    for (auto triangle : triangles)
    {
        geometry::rasterize_filled_triangle(triangle, color, emit_pixel);
    }
}

bool Polygon2D::cache_clockwise()
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
