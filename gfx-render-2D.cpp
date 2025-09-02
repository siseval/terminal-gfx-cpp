#include "gfx-render-2D.h"

namespace curspp::graphics
{

void GfxRender2D::draw_frame()
{
    clear_frame_buffer(context);

    for (auto primitive : primitives->get_items())
    {
        primitive->rasterize(context);
    }

    draw_frame_buffer(context);
}

std::shared_ptr<Ellipse2D> GfxRender2D::create_ellipse(coord2D position, coord2D radius, Color3 color, double line_thickness)
{
    auto ellipse = std::make_shared<Ellipse2D>();

    ellipse->set_radius(radius);
    ellipse->set_line_thickness(line_thickness);
    ellipse->set_pos(position);
    ellipse->set_color(color);

    return ellipse;
}

void GfxRender2D::write_raster_to_frame_buffer(raster_2D raster, bbox_2D bounds, Color3 color)
{
    for (coord_type i = 0; i < bounds.max.x * bounds.max.y; i++)
    {
        if (raster[i])
        {
            coord2D pos = bounds.min + coord2D{ i % bounds.max.x, i / bounds.max.x };
            write_pixel(context, pos, color);
        }
    }
}

}
