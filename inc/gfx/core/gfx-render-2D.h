#ifndef GFX_RENDER_2D_H
#define GFX_RENDER_2D_H

#include <gfx/core/gfx-primitive-store-2D.h>
#include <gfx/core/render-surface.h>
#include <gfx/primitives/ellipse-2D.h>
#include <gfx/primitives/polyline-2D.h>

namespace gfx::core
{

const types::Color4 GFX_BOUNDS_COLOR = { 255, 255, 255 };
const types::Color4 GFX_ANCHOR_COLOR = { 255, 255, 0 };


class GfxRender2D
{

public:

    GfxRender2D(std::shared_ptr<RenderSurface> surface, gfx::math::Vec2d viewport_scaling = gfx::math::Vec2d { 1, 1 }) 
        : surface(surface), primitives(std::make_shared<GfxPrimitiveStore2D>()), viewport_scaling(viewport_scaling) {}

    void draw_frame() const;

    gfx::math::Matrix3x3d get_global_transform() const;

    std::shared_ptr<gfx::primitives::Ellipse2D> create_ellipse(const gfx::math::Vec2d position, const gfx::math::Vec2d radius, const types::Color4 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Polyline2D> create_polyline(const gfx::math::Vec2d position, const std::vector<gfx::math::Vec2d> points, const types::Color4 color, const double line_thickness = 1.0) const;

    inline gfx::math::Vec2i get_resolution() const { return surface->get_resolution() / get_viewport_scaling(); }
    inline gfx::math::Vec2d center() const { return get_resolution() / 2; };

    inline std::shared_ptr<GfxPrimitiveStore2D> get_primitives() const { return primitives; };

    inline void add_item(const std::shared_ptr<GfxPrimitive2D> item) { primitives->add_item(item); }
    inline void remove_item(const std::shared_ptr<GfxPrimitive2D> item) { primitives->remove_item(item); }
    inline int num_items() const { return primitives->num_items(); }

    inline gfx::math::Vec2d get_viewport_scaling() const { return viewport_scaling; }
    inline void set_viewport_scaling(const gfx::math::Vec2d scaling) { viewport_scaling = scaling; }

private:

    std::shared_ptr<RenderSurface> surface;
    std::shared_ptr<GfxPrimitiveStore2D> primitives;
    math::Vec2d viewport_scaling;
};

}

#endif // GFX_RENDER_2D_H
