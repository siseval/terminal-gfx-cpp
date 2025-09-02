#include "ellipse-2D.h"

namespace curspp::graphics
{

void Ellipse2D::update_bounds()
{
    coord2D size = radius * 2 + Vec2d::create(get_line_thickness()) + coord2D { 2, 2 };
    if (rotation != 0.0)
    {
        double rotation = get_rotation();
        Vec2d radius_sin = radius * std::sin(rotation);
        Vec2d radius_cos = radius * std::cos(rotation);

        size.x = 2 * (std::sqrt(radius_cos.x * radius_cos.x) + std::sqrt(radius_sin.y * radius_sin.y));
        size.y = 2 * (std::sqrt(radius_sin.x * radius_sin.x) + std::sqrt(radius_cos.y * radius_cos.y));
    }
    set_size(size + Vec2d::create(get_line_thickness()));
}


void Ellipse2D::rasterize(std::shared_ptr<gfx_context> context)
{
    coord2D radius = scale_with_viewport(context, get_radius());
    coord2D bounds_size = scale_with_viewport(context, get_size());
    coord2D anchor_point = get_anchor() * bounds_size;
    coord2D position = scale_with_viewport(context, get_pos()) - anchor_point;
    coord2D center = (bounds_size / 2);

    if (get_draw_bounds())
    {
        rasterize_bounds(context);
    }

    double thickness = get_line_thickness() / std::min(radius.x, radius.y);

    for (coord_type i = 0; i < bounds_size.x * bounds_size.y; i++)
    {
        coord2D offset = coord2D { i % bounds_size.x, i / bounds_size.x };

        Vec2d relative_pos = { static_cast<double>(offset.x - center.x), static_cast<double>(offset.y - center.y) };
        double rotation = get_rotation();
        Vec2d rotated_pos = rotation != 0.0 ? rotate_point(relative_pos, -rotation) : relative_pos;

        double sdf_result = ((rotated_pos.x * rotated_pos.x) / (radius.x * radius.x)) + ((rotated_pos.y * rotated_pos.y) / (radius.y * radius.y)) - 1;

        if (get_fill() && sdf_result < 0)
        {
            write_pixel(context, position + offset, get_color());
            continue;
        }

        if (std::abs(sdf_result) <= thickness)
        {
            curspp::graphics::rasterize_circle(context, position + offset, line_thickness / 2, get_color());
            // write_pixel(context, position + pos, get_color());
        }
    }
}

}
