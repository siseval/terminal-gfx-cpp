#include "ellipse-2D.h"

namespace curspp::graphics
{

void Ellipse2D::update_bounds(std::shared_ptr<gfx_context> context)
{
    set_size(radius * 2 + Vec2d::create(get_line_thickness()));
}

bbox_2D Ellipse2D::get_transformed_bounds(std::shared_ptr<gfx_context> context)
{
    Matrix3x3d transform = get_transform(context) * get_global_transform(context);
    coord2D corners[4] = {


         coord2D { -radius.x, -radius.y },// * Vec2d { get_anchor().x * 2, get_anchor().y * 2 },
         coord2D { radius.x, -radius.y },// * Vec2d { (1 - get_anchor().x) * 2, get_anchor().y * 2 },
         coord2D { -radius.x,  radius.y },// * Vec2d { get_anchor().x * 2, (1 - get_anchor().y) * 2 },
         coord2D { radius.x,  radius.y },//* Vec2d { (1 - get_anchor().x) * 2, (1 - get_anchor().y) * 2 }


        // coord2D { -radius.x, -radius.y },
        // coord2D { radius.x, -radius.y },
        // coord2D { -radius.x,  radius.y },
        // coord2D { radius.x,  radius.y }
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

    return bbox_2D { min, max };
}


void Ellipse2D::rasterize(std::shared_ptr<gfx_context> context)
{
    update_bounds(context);

    bbox_2D transformed_bounds = get_transformed_bounds(context);
    Matrix3x3d full_transform = get_transform(context) * get_global_transform(context);
    Matrix3x3d inv_transform = invert_affine(full_transform);

    Vec2d anchor_offset = get_anchor() * (get_radius() * 2);
    if (get_draw_bounds())
    {
        rasterize_bounds(context, bbox_2D { { transformed_bounds.min + anchor_offset }, { transformed_bounds.max + anchor_offset } });
        // rasterize_anchor(context, transformed_bounds.min + anchor_offset * 2);
    }

    for (coord_type y = transformed_bounds.min.y; y < transformed_bounds.max.y; ++y)
    {
        for (coord_type x = transformed_bounds.min.x; x < transformed_bounds.max.x; ++x)
        {
            Vec2d global_pixel = Vec2d { static_cast<double>(x), static_cast<double>(y) };
            Vec2d local_pixel = apply_transform(global_pixel, inv_transform);

            double sdf = (local_pixel.x * local_pixel.x) / (radius.x * radius.x) +
                         (local_pixel.y * local_pixel.y) / (radius.y * radius.y) - 1;

            if (std::abs(sdf) < 0.1)
            {
                write_pixel(context, coord2D { x, y }, get_color());
            }
        }
    }
}

}
