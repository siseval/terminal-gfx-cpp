#include "gfx-utils-rasterize.h"

namespace curspp::gfx::utils
{

void rasterize_circle(std::shared_ptr<GfxContext2D> context, const Vec2d center, const double radius, const Color3 color, const Vec2d scale)
{
    Vec2d scaled_radius = Vec2d::create(radius) * scale;

    for (int y = -scaled_radius.y; y <= scaled_radius.y; y++)
    {
        for (int x = -scaled_radius.x; x <= scaled_radius.x; x++)
        {
            if (x * x + y * y <= scaled_radius.x * scaled_radius.y)
            {
                context->write_pixel(center.round() + Vec2i { x, y }, color);
            }
        }
    }
}

void rasterize_line(std::shared_ptr<GfxContext2D> context, const Vec2d start, const Vec2d end, const double line_thickness, const Color3 color)
{
    Vec2d direction = (end - start).normalize();
    Vec2d cur_pos = start;

    while (Vec2d::distance(cur_pos, end) > 1)
    {
        if (line_thickness > 1.0)
        {
            rasterize_circle(context, cur_pos, line_thickness / 2, color, context->get_viewport_scaling());
        }
        else
        {
            context->write_pixel(cur_pos.round(), color);
        }
        cur_pos += direction;
    }
}

void rasterize_box_corners(std::shared_ptr<GfxContext2D> context, const Box2d bounds)
{
    Box2i rounded_bounds = { bounds.min.round(), bounds.max.round() };
    context->write_pixel(rounded_bounds.min, GFX_BOUNDS_COLOR);
    context->write_pixel({ rounded_bounds.min.x, rounded_bounds.max.y }, GFX_BOUNDS_COLOR);
    context->write_pixel(rounded_bounds.max, GFX_BOUNDS_COLOR);
    context->write_pixel({ rounded_bounds.max.x, rounded_bounds.min.y }, GFX_BOUNDS_COLOR);
}

void rasterize_point(std::shared_ptr<GfxContext2D> context, const Vec2d pos)
{
    context->write_pixel(pos.round(), GFX_ANCHOR_COLOR);
    // rasterize_line(context, pos - coord2D{ 5, 0 }, pos + coord2D{ 5, 0 }, 1.0, GFX_ANCHOR_COLOR);
    // rasterize_line(context, pos - coord2D{ 0, 5 }, pos + coord2D{ 0, 5 }, 1.0, GFX_ANCHOR_COLOR);
}

}
