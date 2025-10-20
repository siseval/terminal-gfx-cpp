#include <gfx/primitives/ellipse-2D.h>
#include <gfx/utils/transform.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::math;


Box2d Ellipse2D::get_geometry_size() const
{
    return Box2d { Vec2d::zero(), radius * 2 };
}

Box2d Ellipse2D::get_axis_aligned_bounding_box(const Matrix3x3d &transform) const
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


bool Ellipse2D::point_collides(const gfx::math::Vec2d point, const gfx::math::Matrix3x3d &transform) const
{
    Matrix3x3d inverse_transform { utils::invert_affine(transform) };
    Vec2d local_point { utils::transform_point(point, inverse_transform) - radius };

    return 
    (local_point.x * local_point.x) / (radius.x * radius.x) + 
    (local_point.y * local_point.y) / (radius.y * radius.y) <= 1.0;
}

void Ellipse2D::rasterize(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
{
    if (radius.x <= 0 || radius.y <= 0)
    {
        return;
    }

    double line_extent { line_thickness / 2.0 };
    Box2d AABB { get_axis_aligned_bounding_box(transform) };
    Matrix3x3d inverse_transform { utils::invert_affine(transform) };
    for (int y = AABB.min.y; y <= AABB.max.y; y++)
    {
        for (int x = AABB.min.x; x <= AABB.max.x; x++)
        {
            Vec2d pos { utils::transform_point(Vec2d { static_cast<double>(x) , static_cast<double>(y) }, inverse_transform) - radius };
            Vec2d r_outer { radius + Vec2d(line_extent) };
            Vec2d r_inner { radius - Vec2d(line_extent) };

            double sdf_outer { (pos.x * pos.x) / (r_outer.x * r_outer.x) + (pos.y * pos.y) / (r_outer.y * r_outer.y) };
            double sdf_inner { (pos.x * pos.x) / (r_inner.x * r_inner.x) + (pos.y * pos.y) / (r_inner.y * r_inner.y) };

            if (sdf_outer <= 1.0 && (get_filled() || sdf_inner >= 1.0))
            {
                surface->write_pixel({ x, y }, get_color(), get_depth());
                continue;
            }
        }
    }
}

// void Ellipse2D::rasterize_polygon_ring(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
// {
//     std::vector<Vec2d> outer_ring;
//     std::vector<Vec2d> inner_ring;
//     double line_extent = line_thickness / 2.0;
//
//     for (int i = 0; i < SEGMENTS; ++i)
//     {
//         double progress = static_cast<double>(i) / static_cast<double>(SEGMENTS);
//         double theta = 2.0 * std::numbers::pi * progress;
//
//         double outer_x = (radius.x + line_extent) * std::cos(theta) + radius.x;
//         double outer_y = (radius.y + line_extent) * std::sin(theta) + radius.y;
//         outer_ring.push_back(Vec2d { outer_x, outer_y });
//
//         double inner_x = (radius.x - line_extent) * std::cos(theta) + radius.x;
//         double inner_y = (radius.y - line_extent) * std::sin(theta) + radius.y;
//         inner_ring.push_back(Vec2d { inner_x, inner_y });
//     }
//
//     std::vector<Vec2d> transformed_outer_ring = utils::transform_points(outer_ring, transform);
//     std::vector<Vec2d> transformed_inner_ring = utils::transform_points(inner_ring, transform);
//
//     for (int i = 0; i < SEGMENTS; ++i)
//     {
//         Vec2d v0 = transformed_outer_ring[i];
//         Vec2d v1 = transformed_outer_ring[(i + 1) % SEGMENTS];
//         Vec2d v2 = transformed_inner_ring[i];
//         Vec2d v3 = transformed_inner_ring[(i + 1) % SEGMENTS];
//
//         utils::rasterize_filled_triangle(surface, Triangle { v0, v1, v2 }, get_color());
//         utils::rasterize_filled_triangle(surface, Triangle { v1, v3, v2 }, get_color());
//     }
// }


}
