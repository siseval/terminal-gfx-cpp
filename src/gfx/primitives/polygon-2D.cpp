#include <gfx/primitives/polygon-2D.h>
#include <gfx/utils/transform.h>
#include <gfx/geometry/triangulate.h>

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

void Polygon2D::rasterize_filled_triangle(std::shared_ptr<RenderSurface> surface, const Triangle &triangle) const
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

void Polygon2D::rasterize(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
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
        rasterize_filled_triangle(surface, triangle);
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
