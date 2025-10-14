#ifndef GFX_RENDER_2D_H
#define GFX_RENDER_2D_H

#include <gfx/core/scene-graph-2D.h>
#include <gfx/core/render-surface.h>
#include <gfx/core/types/color4.h>
#include <gfx/core/types/bitmap.h>
#include <gfx/primitives/circle-2D.h>
#include <gfx/primitives/ellipse-2D.h>
#include <gfx/primitives/polyline-2D.h>
#include <gfx/primitives/text-2D.h>
#include <gfx/primitives/bitmap-2D.h>
#include <gfx/text/font-manager-ttf.h>

namespace gfx::core
{

const types::Color4 GFX_BOUNDS_COLOR { 255, 255, 255 };
const types::Color4 GFX_ANCHOR_COLOR { 255, 255, 0 };


class GfxRender2D
{

public:

    GfxRender2D(std::shared_ptr<RenderSurface> surface, gfx::math::Vec2d viewport_scaling = gfx::math::Vec2d { 1, 1 }) : 
        surface(surface), 
        scene_graph(std::make_shared<SceneGraph2D>()), 
        font_manager(std::make_shared<gfx::text::FontManagerTTF>()),
        viewport_scaling(viewport_scaling) {}

    void draw_frame() const;

    gfx::math::Matrix3x3d get_global_transform() const;

    std::shared_ptr<gfx::primitives::Circle2D> create_circle(const gfx::math::Vec2d position, const double radius, const types::Color4 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Ellipse2D> create_ellipse(const gfx::math::Vec2d position, const gfx::math::Vec2d radius, const types::Color4 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Polyline2D> create_polyline(const gfx::math::Vec2d position, const std::vector<gfx::math::Vec2d> &points, const types::Color4 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Bitmap2D> create_bitmap(const gfx::math::Vec2d position, const types::Bitmap &bm) const;
    std::shared_ptr<gfx::primitives::Bitmap2D> create_bitmap(const gfx::math::Vec2d position, const gfx::math::Vec2i resolution) const;

    inline void set_resolution(const gfx::math::Vec2i new_resolution) { surface->resize(new_resolution); }
    inline gfx::math::Vec2i get_resolution() const { return surface->get_resolution() / get_viewport_scaling(); }
    inline gfx::math::Vec2d center() const { return get_resolution() / 2; };
    inline gfx::math::Vec2d get_aspect_ratio() const { return gfx::math::Vec2d { static_cast<double>(get_resolution().x) / get_resolution().y, 1.0 }; }

    inline std::shared_ptr<SceneGraph2D> get_scene_graph() const { return scene_graph; };
    inline std::shared_ptr<RenderSurface> get_render_surface() const { return surface; };
    inline std::shared_ptr<gfx::text::FontManagerTTF> get_font_manager() const { return font_manager; };

    inline void add_item(const std::shared_ptr<GfxPrimitive2D> item) { scene_graph->add_item(item); }
    inline void add_item(const std::shared_ptr<GfxPrimitive2D> item, const std::shared_ptr<GfxPrimitive2D> parent) { scene_graph->add_item(item, parent); }
    inline void remove_item(const std::shared_ptr<GfxPrimitive2D> item) { scene_graph->remove_item(item); }
    inline void clear_items() { scene_graph->clear(); }

    inline int num_items() const { return scene_graph->num_items(); }
    inline bool contains_item(const std::shared_ptr<GfxPrimitive2D> item) const { return scene_graph->contains_item(item); }

    inline gfx::math::Vec2d get_viewport_scaling() const { return viewport_scaling; }
    inline void set_viewport_scaling(const gfx::math::Vec2d scaling) { viewport_scaling = scaling; }

private:

    std::vector<std::pair<std::shared_ptr<GfxPrimitive2D>, gfx::math::Matrix3x3d>> get_draw_queue() const;

    std::shared_ptr<RenderSurface> surface;
    std::shared_ptr<SceneGraph2D> scene_graph;
    std::shared_ptr<gfx::text::FontManagerTTF> font_manager;

    math::Vec2d viewport_scaling;
};

}

#endif // GFX_RENDER_2D_H
