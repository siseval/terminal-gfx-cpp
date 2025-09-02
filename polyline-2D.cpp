#include "polyline-2D.h"

namespace curspp::graphics
{


void Polyline2D::rasterize(std::shared_ptr<gfx_context> context)
{
    if (points.size() < 2)
    {
        return;
    }
    for (coord_type i = 0; i < points.size() - 1; i++)
    {
        rasterize_line(context, scale_with_viewport(context, points[i]), scale_with_viewport(context, points[i + 1]), get_line_thickness(), get_color());
    }
}

void Polyline2D::update_bounds()
{
    if (points.size() < 2)
    {
        set_bounds({ {0, 0}, {0, 0} });
        return;
    }

    coord2D min_point = points[0];
    coord2D max_point = points[0];

    for (const coord2D& point : points)
    {
        if (point.x < min_point.x) min_point.x = point.x;
        if (point.y < min_point.y) min_point.y = point.y;
        if (point.x > max_point.x) max_point.x = point.x;
        if (point.y > max_point.y) max_point.y = point.y;
    }

    coord2D line_extent = coord2D { static_cast<coord_type>(get_line_thickness()), static_cast<coord_type>(get_line_thickness()) };
    bbox_2D new_bounds = { min_point - line_extent - coord2D { 1, 1 }, max_point + line_extent + coord2D { 1, 1 } };
    set_bounds(new_bounds);
}



}
