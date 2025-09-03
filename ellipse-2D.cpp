#include "ellipse-2D.h"

namespace curspp::graphics
{

void Ellipse2D::update_bounds(std::shared_ptr<gfx_context> context)
{
    Matrix3x3d transform = get_transform(context);
    coord2D corners[4] = {
        coord2D { -radius.x, -radius.y },
        coord2D { radius.x, -radius.y },
        coord2D { -radius.x,  radius.y },
        coord2D { radius.x,  radius.y }
    };

    for (uint8_t i = 0; i < 4; ++i)
    {
        corners[i] = apply_transform(corners[i], transform);
    }

    coord2D min = { corners[0].x, corners[0].y };
    coord2D max = { corners[0].x, corners[0].y };

    for (uint8_t i = 0; i < 4; ++i)
    {
        if (corners[i].x < min.x)
        {
            min.x = corners[i].x;
        }
        if (corners[i].y < min.y)
        {
            min.y = corners[i].y;
        }
        if (corners[i].x > max.x)
        {
            max.x = corners[i].x;
        }
        if (corners[i].y > max.y)
        {
            max.y = corners[i].y;
        }
    }

    set_size(max - min);
}


void Ellipse2D::rasterize(std::shared_ptr<gfx_context> context)
{
    update_bounds(context);

    coord2D radius = get_radius();
    coord2D bounds_size = get_size();
    coord2D anchor_point = get_anchor() * bounds_size;
    coord2D position = get_pos();
    coord2D center = (bounds_size / 2);

    Matrix3x3d transform = get_inverse_transform(context);

    if (get_draw_bounds())
    {
        rasterize_bounds(context);
    }

    for (coord_type i = 0; i < bounds_size.x * bounds_size.y; i++)
    {
        coord2D offset = coord2D { i % bounds_size.x, i / bounds_size.x };

        // Vec2d relative_pos = { static_cast<double>(offset.x - center.x), static_cast<double>(offset.y - center.y) };
        double rotation = get_rotation();
        // Vec2d rotated_pos = rotation != 0.0 ? rotate_point(relative_pos, -rotation) : relative_pos;
        Vec2d rotated_pos = curspp::graphics::apply_transform(offset, transform);

        double sdf_result = ((rotated_pos.x * rotated_pos.x) / (radius.x * radius.x)) + ((rotated_pos.y * rotated_pos.y) / (radius.y * radius.y)) - 1;

        // double sdf_result = ((rotated_pos.x * rotated_pos.x) + (rotated_pos.y * rotated_pos.y)) - 1;

        if (get_fill() && sdf_result < 0)
        {
            write_pixel(context, position + offset, get_color());
            continue;
        }

        if (sdf_result > 0.9 && sdf_result < 1.1)
        {
            // curspp::graphics::rasterize_circle(context, position + offset, line_thickness / 2, get_color());
            write_pixel(context, position + offset - anchor_point, get_color());
        }
    }
}

}
