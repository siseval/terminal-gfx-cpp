#include "gfx-primitive-2D.h"

namespace curspp::graphics
{

void GfxPrimitive2D::set_pos(const coord2D pos) 
{ 
    coord2D size = bounds.max - bounds.min;
    bounds.min = pos - anchor; 
    bounds.max = bounds.min + size;
    update_bounds();
}

void GfxPrimitive2D::rasterize_bounds(std::shared_ptr<gfx_context> context)
{
    coord2D bounds_size = scale_with_viewport(context, get_size());
    coord2D position = scale_with_viewport(context, get_pos());
    coord2D center = (bounds_size / 2);

    write_pixel(context, position + center, GFX_BOUNDS_COLOR);
    write_pixel(context, position, GFX_BOUNDS_COLOR);
    write_pixel(context, position + coord2D{ 0, bounds_size.y }, GFX_BOUNDS_COLOR);
    write_pixel(context, position + bounds_size, GFX_BOUNDS_COLOR);
    write_pixel(context, position + coord2D{ bounds_size.x, 0 }, GFX_BOUNDS_COLOR);
}

void rasterize_line(std::shared_ptr<gfx_context> context, const coord2D start, const coord2D end, double line_thickness, const Color3 color)
{
    coord_type delta_x = std::abs(end.x - start.x);
    int8_t sign_x = start.x < end.x ? 1 : - 1;

    coord_type delta_y = -std::abs(end.y - start.y);
    int8_t sign_y = start.y < end.y ? 1 : - 1;

    coord_type error = delta_x + delta_y;
    coord2D cur_pos = start;

    coord_type line_extent = line_thickness / 2;

    // vec2f normal_vector = curspp::vec2f::normal(curspp::vec2f::normalize(end - start));
    while (true)
    {
        // for (coord_type i = 0; i < line_thickness ; i++)
        // {
        //     vec2f offset = scale_with_viewport(context, (normal_vector * (i - line_extent)));
        //     write_pixel(context, cur_pos + offset, get_color());
        // }
        rasterize_circle(context, cur_pos, line_extent, color);

        coord_type error_doubled = 2 * error;

        if (error_doubled >= delta_y)
        {
            if (cur_pos.x == end.x)
            {
                break;
            }
            error += delta_y;
            cur_pos.x += sign_x;
        }
        if (error_doubled <= delta_x)
        {
            if (cur_pos.y == end.y)
            {
                break;
            }
            error += delta_x;
            cur_pos.y += sign_y;
        }
    }
}

void rasterize_circle(std::shared_ptr<gfx_context> context, const coord2D center, const double radius, const Color3 color)
{
    vec2d scaled_radius = vec2d { radius, radius } * context->viewport_scaling;
    coord_type diameter = radius * 2;
    for (coord_type i = 0; i < diameter * diameter; i++)
    {
        coord2D pos = scale_with_viewport(context, { i % diameter - static_cast<coord_type>(radius), i / diameter - static_cast<coord_type>(radius)});
        double sdf = ((pos.x * pos.x) / (scaled_radius.x * scaled_radius.x)) + ((pos.y * pos.y) / (scaled_radius.y * scaled_radius.y)) - 1;

        if (sdf <= radius)
        {
            write_pixel(context, center + pos, color);
        }
    }
}

vec2d rotate_point(const coord2D point, const double angle)
{
    double s = sin(angle);
    double c = cos(angle);

    double xnew = point.x * c - point.y * s;
    double ynew = point.x * s + point.y * c;

    return { xnew, ynew };
}


}


