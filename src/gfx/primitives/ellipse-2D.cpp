#include <gfx/primitives/ellipse-2D.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::math;


Box2d Ellipse2D::get_relative_extent() const
{
    return { { 0, 0 }, { radius * 2 } };
}

void Ellipse2D::rasterize_filled(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
{
    double line_extent = line_thickness / 2.0;
    Box2d AABB = get_axis_aligned_bounding_box(transform);
    Matrix3x3d inverse_transform = utils::invert_affine(transform);
    for (int y = AABB.min.y; y <= AABB.max.y; y++)
    {
        for (int x = AABB.min.x; x <= AABB.max.x; x++)
        {
            Vec2d local_pos = utils::transform_point(Vec2d { static_cast<double>(x) , static_cast<double>(y) }, inverse_transform) - radius;
            Vec2d outer_r = radius + Vec2d::create(line_extent);
            double sdf = (local_pos.x * local_pos.x) / (outer_r.x * outer_r.x) + (local_pos.y * local_pos.y) / (outer_r.y * outer_r.y);

            if (get_fill() && sdf <= 1.0)
            {
                surface->write_pixel({ x, y }, get_color());
                continue;
            }
        }
    }

}

void Ellipse2D::rasterize_polygon_ring(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
{
    std::vector<Vec2d> outer_ring;
    std::vector<Vec2d> inner_ring;
    double line_extent = line_thickness / 2.0;

    for (int i = 0; i < SEGMENTS; ++i)
    {
        double progress = static_cast<double>(i) / static_cast<double>(SEGMENTS);
        double theta = 2.0 * M_PI * progress;

        double outer_x = (radius.x + line_extent) * std::cos(theta) + radius.x;
        double outer_y = (radius.y + line_extent) * std::sin(theta) + radius.y;
        outer_ring.push_back(Vec2d { outer_x, outer_y });

        double inner_x = (radius.x - line_extent) * std::cos(theta) + radius.x;
        double inner_y = (radius.y - line_extent) * std::sin(theta) + radius.y;
        inner_ring.push_back(Vec2d { inner_x, inner_y });
    }

    std::vector<Vec2d> transformed_outer_ring = utils::transform_points(outer_ring, transform);
    std::vector<Vec2d> transformed_inner_ring = utils::transform_points(inner_ring, transform);

    for (int i = 0; i < SEGMENTS; ++i)
    {
        Vec2d v0 = transformed_outer_ring[i];
        Vec2d v1 = transformed_outer_ring[(i + 1) % SEGMENTS];
        Vec2d v2 = transformed_inner_ring[i];
        Vec2d v3 = transformed_inner_ring[(i + 1) % SEGMENTS];

        utils::rasterize_filled_triangle(surface, Triangle { v0, v1, v2 }, get_color());
        utils::rasterize_filled_triangle(surface, Triangle { v1, v3, v2 }, get_color());
    }
}

void Ellipse2D::rasterize(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
{
    if (radius.x <= 0 || radius.y <= 0)
    {
        return;
    }

    if (get_fill())
    {
        rasterize_filled(surface, transform);
    }
    else
    {
        rasterize_polygon_ring(surface, transform);
    }
}


}
