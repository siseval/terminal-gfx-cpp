#ifndef GFX_RENDER_2D_H
#define GFX_RENDER_2D_H

#include "gfx-context.h"
#include "gfx-primitive-store_2D.h"
#include "ellipse-2D.h"

namespace curspp::graphics
{


class GfxRender2D
{
    public:

    GfxRender2D(std::shared_ptr<gfx_context> ctx) : context(ctx), primitives(std::make_shared<GfxPrimitiveStore2D>()) {};

    GfxRender2D(coord2D resolution, coord2D origin = coord2D { 0, 0 }) 
        : context(create_context(resolution, origin)), primitives(std::make_shared<GfxPrimitiveStore2D>()) {};
            
    void draw_frame();

    std::shared_ptr<Ellipse2D> create_ellipse(coord2D position, coord2D radius, Color3 color, double line_thickness = 1.0);

    inline coord2D get_center() { return context->resolution / (context->viewport_scaling * 2); };
    inline coord2D scaled_coord(coord2D vec) { return scale_with_viewport(context, vec); };

    inline std::shared_ptr<GfxPrimitiveStore2D> get_primitives() const { return primitives; };
    inline std::shared_ptr<gfx_context> get_context() const { return context; };

    private:

    std::shared_ptr<gfx_context> context;
    std::shared_ptr<GfxPrimitiveStore2D> primitives;

    void write_raster_to_frame_buffer(raster_2D raster, bbox_2D bounds, Color3 color);
};

}

#endif // GFX_RENDER_2D_H
