#include "ellipse-2D.h"

namespace curspp::graphics
{

void Ellipse2D::update_bounds()
{
    coord2D size = radius * 2;
    coord2D position = get_pos();
    coord2D line_extent = coord2D { static_cast<coord_type>(get_line_thickness()), static_cast<coord_type>(get_line_thickness()) };
    bbox_2D new_bounds = { -coord2D{ 1, 1 } - line_extent + position, position + size + line_extent + coord2D { 1, 1 } };
    set_bounds(new_bounds);
}


void Ellipse2D::rasterize(std::shared_ptr<gfx_context> context)
{
    coord2D radius = scale_with_viewport(context, get_radius());
    coord2D bounds_size = scale_with_viewport(context, get_size());
    coord2D position = scale_with_viewport(context, get_pos());
    coord2D center = (bounds_size / 2);

    if (get_draw_bounds())
    {
        rasterize_bounds(context);
    }

    double thickness = get_line_thickness() / std::min(radius.x, radius.y);

    for (coord_type i = 0; i < bounds_size.x * bounds_size.y; i++)
    {
        coord2D pos = coord2D { i % bounds_size.x, i / bounds_size.x };

        vec2d relative_pos = { static_cast<double>(pos.x - center.x), static_cast<double>(pos.y - center.y) };
        double rotation = get_rotation();
        vec2d rotated_pos = rotation != 0.0 ? rotate_point(relative_pos, -rotation) : relative_pos;

        double sdf = ((rotated_pos.x * rotated_pos.x) / (radius.x * radius.x)) + ((rotated_pos.y * rotated_pos.y) / (radius.y * radius.y)) - 1;

        if (get_fill() && sdf < 0)
        {
            write_pixel(context, position + pos, get_color());
            continue;
        }

        if (std::abs(sdf) <= thickness)
        {
            write_pixel(context, position + pos, get_color());
        }
    }
}

}
