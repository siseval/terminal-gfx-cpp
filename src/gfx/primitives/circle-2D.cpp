#include <gfx/primitives/circle-2D.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::math;


Box2d Circle2D::get_relative_extent() const
{
    return { { 0, 0 }, Vec2d::create(radius * 2) };
}


void Circle2D::rasterize(std::shared_ptr<RenderSurface> surface, const Matrix3x3d &transform) const
{
    if (radius <= 0)
    {
        return;
    }

    double line_extent = line_thickness / 2.0;
    Box2d AABB = get_axis_aligned_bounding_box(transform);
    Matrix3x3d inverse_transform = utils::invert_affine(transform);
    for (int y = AABB.min.y; y <= AABB.max.y; y++)
    {
        for (int x = AABB.min.x; x <= AABB.max.x; x++)
        {
            Vec2d pos = utils::transform_point(Vec2d { static_cast<double>(x) , static_cast<double>(y) }, inverse_transform) - Vec2d::create(radius);
            double r_outer = radius + line_extent;
            double r_inner = radius - line_extent;

            double distance = std::sqrt(pos.x * pos.x + pos.y * pos.y);

            if (distance <= r_outer && (get_fill() || distance >= r_inner))
            {
                surface->write_pixel({ x, y }, get_color());
                continue;
            }
        }
    }
}

}
