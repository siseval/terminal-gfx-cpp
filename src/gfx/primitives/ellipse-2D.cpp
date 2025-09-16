#include <gfx/primitives/ellipse-2D.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::math;


Box2d Ellipse2D::get_relative_extent() const
{
    return { { 0, 0 }, { radius * 2 } };
}

void Ellipse2D::rasterize(std::shared_ptr<RenderSurface> surface, const Matrix3x3d transform) const
{
    Box2d global_bounds = get_global_bounds(transform);
    Matrix3x3d inv_transform = utils::invert_affine(transform);

    for (int y = global_bounds.min.y; y < global_bounds.max.y; ++y)
    {
        for (int x = global_bounds.min.x; x < global_bounds.max.x; ++x)
        {
            Vec2d global_pixel = Vec2d { static_cast<double>(x), static_cast<double>(y) };
            Vec2d local_pixel = utils::apply_transform(global_pixel, inv_transform) - radius;

            double sdf = (local_pixel.x * local_pixel.x) / (radius.x * radius.x) +
                         (local_pixel.y * local_pixel.y) / (radius.y * radius.y) - 1;

            if (get_fill() > 0 && sdf < 0)
            {
                surface->write_pixel(Vec2i { x, y }, get_color());
            }
            double sdf_threshold = 1.0 / (std::min(radius.x, radius.y) * std::min(scale.x, scale.y));
            if (std::abs(sdf) < sdf_threshold)
            {
                utils::rasterize_circle(surface, Vec2i { x, y }, get_line_thickness() / 2, get_color());
            }
        }
    }
}


}
