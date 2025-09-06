#include "polyline-2D.h"

namespace curspp::graphics
{

BBox2D Polyline2D::get_relative_extent() const
{
    Vec2d min = Vec2d::zero();
    Vec2d max = Vec2d::zero();

    for (auto point : points)
    {
        if (point.x < min.x)
        {
            min.x = point.x;
        }
        if (point.x > max.x)
        {
            max.x = point.x;
        }
        if (point.y < min.y)
        {
            min.y = point.y;
        }
        if (point.y > max.y)
        {
            max.y = point.y;
        }
    }

    return { min, max };
}

void Polyline2D::rasterize(std::shared_ptr<gfx_context> context) const
{
    if (points.size() < 2)
    {
        return;
    }
    Matrix3x3d full_transform = get_global_transform(context) * get_transform();
    for (int i = 0; i < points.size() - 1; i++)
    {
        Vec2d transformed_start = apply_transform(points[i], full_transform);
        Vec2d transformed_end = apply_transform(points[i + 1], full_transform);
        rasterize_line(context, transformed_start, transformed_end, get_line_thickness(), get_color());
    }
    if (do_close)
    {
        Vec2d transformed_start = apply_transform(points.front(), full_transform);
        Vec2d transformed_end = apply_transform(points.back(), full_transform);
        rasterize_line(context, transformed_start, transformed_end, get_line_thickness(), get_color());
    }
}

// void Polyline2D::update_bounds(std::shared_ptr<gfx_context> context)
// {
//     if (points.size() < 2)
//     {
//         // set_size({ 0, 0 });
//         return;
//     }
//
//     coord2D min_point = points[0];
//     coord2D max_point = points[0];
//
//     for (const coord2D& point : points)
//     {
//         if (point.x < min_point.x) min_point.x = point.x;
//         if (point.y < min_point.y) min_point.y = point.y;
//         if (point.x > max_point.x) max_point.x = point.x;
//         if (point.y > max_point.y) max_point.y = point.y;
//     }
//
//     set_size(max_point + Vec2d::create(get_line_thickness()));
// }



}
