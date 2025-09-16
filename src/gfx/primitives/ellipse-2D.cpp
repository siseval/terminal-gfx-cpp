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
    std::vector<Vec2d> outer_ring;
    std::vector<Vec2d> inner_ring;
    double line_extent = line_thickness / 2.0;

    for (int i = 0; i < SEGMENTS; ++i)
    {
        double theta = 2.0 * M_PI * double(i) / double(SEGMENTS);

        double outer_x = (radius.x + line_extent) * std::cos(theta) + radius.x;
        double outer_y = (radius.y + line_extent) * std::sin(theta) + radius.y;
        outer_ring.push_back(Vec2d { outer_x, outer_y });

        double inner_x = (radius.x - line_extent) * std::cos(theta) + radius.x;
        double inner_y = (radius.y - line_extent) * std::sin(theta) + radius.y;
        inner_ring.push_back(Vec2d { inner_x, inner_y });
    }

    std::vector<Vec2d> transformed_outer_ring = utils::apply_transform(outer_ring, transform);
    std::vector<Vec2d> transformed_inner_ring = utils::apply_transform(inner_ring, transform);

    for (int i = 0; i < SEGMENTS; ++i)
    {
        Vec2d v0 = transformed_outer_ring[i];
        Vec2d v1 = transformed_outer_ring[(i + 1) % SEGMENTS];
        Vec2d v2 = transformed_inner_ring[i];
        Vec2d v3 = transformed_inner_ring[(i + 1) % SEGMENTS];

        utils::rasterize_filled_triangle(surface, v0, v1, v2, get_color());
        utils::rasterize_filled_triangle(surface, v1, v3, v2, get_color());
    }

    if (get_fill())
    {
        utils::rasterize_filled_polygon(surface, transformed_outer_ring, get_color());
    }
}

    // for (int y = global_bounds.min.y; y < global_bounds.max.y; ++y)
    // {
    //     for (int x = global_bounds.min.x; x < global_bounds.max.x; ++x)
    //     {
    //         Vec2d global_pixel = Vec2d { static_cast<double>(x), static_cast<double>(y) };
    //         Vec2d local_pixel = utils::apply_transform(global_pixel, inv_transform) - radius;
    //
    //         double sdf = (local_pixel.x * local_pixel.x) / (radius.x * radius.x) +
    //                      (local_pixel.y * local_pixel.y) / (radius.y * radius.y) - 1;
    //
    //         if (get_fill() > 0 && sdf < 0)
    //         {
    //             surface->write_pixel(Vec2i { x, y }, get_color());
    //         }
    //         double sdf_threshold = 1.0 / (std::min(radius.x, radius.y) * std::min(scale.x, scale.y));
    //         if (std::abs(sdf) < sdf_threshold)
    //         {
    //             utils::rasterize_circle(surface, Vec2i { x, y }, get_line_thickness() / 2, get_color());
    //         }
    //     }
    // }


}
