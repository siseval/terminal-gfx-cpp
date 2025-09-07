#include "ellipse-2D.h"

namespace curspp::graphics
{

Box2d Ellipse2D::get_relative_extent() const
{
    return { { 0, 0 }, { radius * 2 } };
}

void Ellipse2D::rasterize(std::shared_ptr<GfxContext2D> context) const
{
    Box2d global_bounds = get_global_bounds(context);
    Matrix3x3d full_transform = context->get_transform() * get_transform();
    Matrix3x3d inv_transform = invert_affine(full_transform);

    for (int y = global_bounds.min.y; y < global_bounds.max.y; ++y)
    {
        for (int x = global_bounds.min.x; x < global_bounds.max.x; ++x)
        {
            Vec2d global_pixel = Vec2d { static_cast<double>(x), static_cast<double>(y) };
            Vec2d local_pixel = apply_transform(global_pixel, inv_transform) - radius;

            double sdf = (local_pixel.x * local_pixel.x) / (radius.x * radius.x) +
                         (local_pixel.y * local_pixel.y) / (radius.y * radius.y) - 1;

            if (get_fill() && sdf < 0)
            {
                context->write_pixel(Vec2i { x, y }, get_color());
            }
            if (std::abs(sdf) < 1.0 / std::min(radius.x, radius.y))
            {
                rasterize_circle(context, Vec2i { x, y }, get_line_thickness() / 2, get_color());
            }
        }
    }
}


}
