#ifndef GFX_RENDER_2D_H
#define GFX_RENDER_2D_H

#include <gfx/core/gfx-context-2D.h>
#include <gfx/core/gfx-primitive-store-2D.h>
#include <gfx/primitives/ellipse-2D.h>
#include <gfx/primitives/polyline-2D.h>

namespace gfx::core
{


class GfxRender2D
{
    public:

    GfxRender2D(std::shared_ptr<GfxContext2D> context) : context(context), primitives(std::make_shared<GfxPrimitiveStore2D>()) {};

    GfxRender2D(gfx::math::Vec2i resolution, gfx::math::Vec2i origin = gfx::math::Vec2i { 0, 0 }) 
        : context(std::make_shared<GfxContext2D>(resolution, origin)), primitives(std::make_shared<GfxPrimitiveStore2D>()) {};
            
    void draw_frame() const;

    std::shared_ptr<gfx::primitives::Ellipse2D> create_ellipse(const gfx::math::Vec2d position, const gfx::math::Vec2d radius, const types::Color3 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Polyline2D> create_polyline(const gfx::math::Vec2d position, const std::vector<gfx::math::Vec2d> points, const types::Color3 color, const double line_thickness = 1.0) const;

    inline gfx::math::Vec2i get_resolution() const { return context->get_resolution() / context->get_viewport_scaling(); }

    inline gfx::math::Vec2d center() const { return get_resolution() / 2; };

    inline std::shared_ptr<GfxPrimitiveStore2D> get_primitives() const { return primitives; };
    inline std::shared_ptr<GfxContext2D> get_context() const { return context; };

    inline void add_item(const std::shared_ptr<GfxPrimitive2D> item) { primitives->add_item(item); }
    inline void remove_item(const std::shared_ptr<GfxPrimitive2D> item) { primitives->remove_item(item); }

    inline int num_items() const { return primitives->num_items(); }

    inline void set_viewport_scaling(const gfx::math::Vec2d scaling) { context->get_viewport_scaling() = scaling; }
    inline gfx::math::Vec2d get_viewport_scaling() const { return context->get_viewport_scaling(); }

    private:

    std::shared_ptr<GfxContext2D> context;
    std::shared_ptr<GfxPrimitiveStore2D> primitives;
};

}

#endif // GFX_RENDER_2D_H
