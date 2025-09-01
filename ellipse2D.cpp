#include "ellipse-2D.h"

namespace curspp::graphics
{

void Ellipse2D::update_bounds()
{
    coord2D size = radius * 2 * coord2D { 1, 1 };
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

    double semi_major = radius.x / 1.0;
    double semi_minor = radius.y / 1.0;
    double thickness = get_line_thickness() / std::min(semi_major, semi_minor);

    write_pixel(context, position + center, get_color());
    write_pixel(context, position, get_color());
    write_pixel(context, position + coord2D{ 0, bounds_size.y }, get_color());
    write_pixel(context, position + bounds_size, get_color());
    write_pixel(context, position + coord2D{ bounds_size.x, 0 }, get_color());

    for (coord_type i = 0; i < bounds_size.x * bounds_size.y; i++)
    {
        coord2D pos = coord2D{ i % bounds_size.x, i / bounds_size.x };

        // write_pixel(context, position() + pos, get_color());

        double relative_x = pos.x - center.x;
        double relative_y = pos.y - center.y;

        double result = ((relative_x * relative_x) / (semi_major * semi_major)) + ((relative_y * relative_y) / (semi_minor * semi_minor));

        if (std::abs(1 - result) <= thickness)
        {
            write_pixel(context, position + pos, get_color());
        }
    }
}

}
