#include "gfx-primitive-2D.h"

namespace curspp::graphics
{

void GfxPrimitive2D::set_pos(const coord2D pos) 
{ 
    coord2D size = bounds.max - bounds.min;
    bounds.min = pos; 
    bounds.max = pos + size;
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


}


