#ifndef GFX_RENDER_2D_H
#define GFX_RENDER_2D_H

#include "gfx-context-2D.h"
#include "gfx-primitive-store-2D.h"
#include "ellipse-2D.h"
#include "polyline-2D.h"

namespace curspp::graphics
{


class GfxRender2D
{
    public:

    GfxRender2D(std::shared_ptr<GfxContext2D> context) : context(context), primitives(std::make_shared<GfxPrimitiveStore2D>()) {};

    GfxRender2D(Vec2i resolution, Vec2i origin = Vec2i { 0, 0 }) 
        : context(std::make_shared<GfxContext2D>(resolution, origin)), primitives(std::make_shared<GfxPrimitiveStore2D>()) {};
            
    void draw_frame() const;

    std::shared_ptr<Ellipse2D> create_ellipse(const Vec2d position, const Vec2d radius, const Color3 color, const double line_thickness = 1.0) const;
    std::shared_ptr<Polyline2D> create_polyline(const Vec2d position, const std::vector<Vec2d> points, const Color3 color, const double line_thickness = 1.0) const;

    inline Vec2i get_resolution() const { return context->get_resolution() / context->get_viewport_scaling(); }

    inline Vec2d center() const { return get_resolution() / 2; };

    inline std::shared_ptr<GfxPrimitiveStore2D> get_primitives() const { return primitives; };
    inline std::shared_ptr<GfxContext2D> get_context() const { return context; };

    inline void add_item(const std::shared_ptr<GfxPrimitive2D> item) { primitives->add_item(item); }
    inline void remove_item(const std::shared_ptr<GfxPrimitive2D> item) { primitives->remove_item(item); }

    inline int num_items() const { return primitives->num_items(); }

    inline void set_viewport_scaling(const Vec2d scaling) { context->get_viewport_scaling() = scaling; }
    inline Vec2d get_viewport_scaling() const { return context->get_viewport_scaling(); }

    private:

    std::shared_ptr<GfxContext2D> context;
    std::shared_ptr<GfxPrimitiveStore2D> primitives;
};

}

#endif // GFX_RENDER_2D_H
