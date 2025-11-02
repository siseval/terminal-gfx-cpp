#include <gfx/primitives/bitmap-2D.h>
#include <gfx/utils/transform.h>

namespace gfx::primitives
{

using namespace gfx::core::types;
using namespace gfx::core;
using namespace gfx::math;

Box2d Bitmap2D::get_geometry_size() const
{
    return Box2d { 
        { 0, 0 }, 
        { 
            static_cast<double>(resolution.x), 
            static_cast<double>(resolution.y) 
        } 
    };
}

bool Bitmap2D::point_collides(const Vec2d point, const Matrix3x3d &transform) const
{
    Matrix3x3d inverse_transform { utils::invert_affine(transform) };
    Vec2d local_point { utils::transform_point(point, inverse_transform) };

    int img_x = static_cast<int>(local_point.x);
    int img_y = static_cast<int>(local_point.y);

    if (img_x >= 0 && img_x < resolution.x && img_y >= 0 && img_y < resolution.y)
    {
        Color4 pixel { get_pixel({ img_x, img_y }) };
        return pixel.a > 0;
    }
    return false;
}

void Bitmap2D::rasterize(const Matrix3x3d &transform, const std::function<void(const Pixel&)> emit_pixel) const
{
    Box2d AABB { get_axis_aligned_bounding_box(transform) };
    Matrix3x3d inverse_transform { utils::invert_affine(transform) };

    for (int y = static_cast<int>(AABB.min.y); y < static_cast<int>(AABB.max.y); ++y)
    {
        for (int x = static_cast<int>(AABB.min.x); x < static_cast<int>(AABB.max.x); ++x)
        {
            Vec2d pos { static_cast<double>(x), static_cast<double>(y) };
            Vec2d local_pos = utils::transform_point(pos, inverse_transform);

            int img_x = static_cast<int>(local_pos.x);
            int img_y = static_cast<int>(local_pos.y);

            if (img_x >= 0 && img_x < resolution.x && img_y >= 0 && img_y < resolution.y)
            {
                Color4 pixel { get_pixel({ img_x, img_y }) };
                if (pixel.a > 0)
                {
                    emit_pixel(Pixel { { x, y }, pixel });
                }
            }
        }
    }
}

}
