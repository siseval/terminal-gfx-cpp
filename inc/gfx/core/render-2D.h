#ifndef RENDER_2D_H
#define RENDER_2D_H

#include <gfx/core/scene-graph-2D.h>
#include <gfx/core/render-surface.h>
#include <gfx/core/types/color4.h>
#include <gfx/core/types/bitmap.h>
#include <gfx/primitives/circle-2D.h>
#include <gfx/primitives/ellipse-2D.h>
#include <gfx/primitives/polyline-2D.h>
#include <gfx/primitives/polygon-2D.h>
#include <gfx/primitives/text-2D.h>
#include <gfx/primitives/bitmap-2D.h>
#include <gfx/text/font-manager-ttf.h>

namespace gfx::core
{

const types::Color4 GFX_BOUNDS_COLOR { 255, 255, 255 };
const types::Color4 GFX_ANCHOR_COLOR { 255, 255, 0 };


class Render2D
{

public:

    Render2D(std::shared_ptr<RenderSurface> surface, gfx::math::Vec2d viewport_scaling = gfx::math::Vec2d { 1, 1 }) : 
        surface(surface), 
        scene_graph(std::make_shared<SceneGraph2D>()), 
        font_manager(std::make_shared<gfx::text::FontManagerTTF>()),
        viewport_scaling(viewport_scaling) 
    {
        surface->init();
    }

    void draw_frame() const;

    gfx::math::Matrix3x3d get_global_transform() const;

    std::shared_ptr<gfx::primitives::Circle2D> create_circle(const gfx::math::Vec2d position, const double radius, const types::Color4 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Circle2D> create_circle(const double x, const double y, const double radius, const types::Color4 color, const double line_thickness = 1.0) const 
    {
        return create_circle(gfx::math::Vec2d { x, y }, radius, color, line_thickness);
    };
    std::shared_ptr<gfx::primitives::Ellipse2D> create_ellipse(const gfx::math::Vec2d position, const gfx::math::Vec2d radius, const types::Color4 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Ellipse2D> create_ellipse(const double x, const double y, const double radius_x, const double radius_y, const types::Color4 color, const double line_thickness = 1.0) const 
    {
        return create_ellipse(gfx::math::Vec2d { x, y }, gfx::math::Vec2d { radius_x, radius_y }, color, line_thickness);
    };
    std::shared_ptr<gfx::primitives::Polyline2D> create_polyline(const gfx::math::Vec2d position, const std::vector<gfx::math::Vec2d> &points, const types::Color4 color, const double line_thickness = 1.0) const;
    std::shared_ptr<gfx::primitives::Polyline2D> create_polyline(const double x, const double y, const std::vector<gfx::math::Vec2d> &points, const types::Color4 color, const double line_thickness = 1.0) const 
    {
        return create_polyline(gfx::math::Vec2d { x, y }, points, color, line_thickness);
    };
    std::shared_ptr<gfx::primitives::Polygon2D> create_polygon(const gfx::math::Vec2d position, const std::vector<gfx::math::Vec2d> &points, const types::Color4 fill_color) const;
    std::shared_ptr<gfx::primitives::Polygon2D> create_polygon(const double x, const double y, const std::vector<gfx::math::Vec2d> &points, const types::Color4 fill_color) const 
    {
        return create_polygon(gfx::math::Vec2d { x, y }, points, fill_color);
    };
    std::shared_ptr<gfx::primitives::Bitmap2D> create_bitmap(const gfx::math::Vec2d position, const types::Bitmap &bm) const;
    std::shared_ptr<gfx::primitives::Bitmap2D> create_bitmap(const double x, const double y, const types::Bitmap &bm) const 
    {
        return create_bitmap(gfx::math::Vec2d { x, y }, bm);
    };
    std::shared_ptr<gfx::primitives::Bitmap2D> create_bitmap(const gfx::math::Vec2d position, const gfx::math::Vec2i resolution) const;
    std::shared_ptr<gfx::primitives::Bitmap2D> create_bitmap(const double x, const double y, const gfx::math::Vec2i resolution) const 
    {
        return create_bitmap(gfx::math::Vec2d { x, y }, resolution);
    };

    bool collides(const gfx::math::Vec2d point, const std::shared_ptr<Primitive2D>) const;
    bool collides(const double x, const double y, const std::shared_ptr<Primitive2D> primitive) const
    {
        return collides(gfx::math::Vec2d { x, y }, primitive);
    };

    inline void set_resolution(const gfx::math::Vec2i new_resolution) { surface->resize(new_resolution); }
    inline void set_resolution(const int width, const int height) { surface->resize(gfx::math::Vec2i { width, height }); }
    inline gfx::math::Vec2i get_resolution() const { return surface->get_resolution() / get_viewport_scaling(); }
    inline gfx::math::Vec2d center() const { return get_resolution() / 2; };
    inline gfx::math::Vec2d get_aspect_ratio() const { return gfx::math::Vec2d { static_cast<double>(get_resolution().x) / get_resolution().y, 1.0 }; }

    inline std::shared_ptr<SceneGraph2D> get_scene_graph() const { return scene_graph; };
    inline std::shared_ptr<RenderSurface> get_render_surface() const { return surface; };
    inline std::shared_ptr<gfx::text::FontManagerTTF> get_font_manager() const { return font_manager; };

    inline void add_item(const std::shared_ptr<Primitive2D> item) { scene_graph->add_item(item); }
    inline void add_item(const std::shared_ptr<Primitive2D> item, const std::shared_ptr<Primitive2D> parent) { scene_graph->add_item(item, parent); }
    inline void remove_item(const std::shared_ptr<Primitive2D> item) { scene_graph->remove_item(item); }
    inline void clear_items() { scene_graph->clear(); }

    inline int num_items() const { return scene_graph->num_items(); }
    inline bool contains_item(const std::shared_ptr<Primitive2D> item) const { return scene_graph->contains_item(item); }

    inline gfx::math::Vec2d get_viewport_scaling() const { return viewport_scaling; }
    inline void set_viewport_scaling(const gfx::math::Vec2d scaling) { viewport_scaling = scaling; }
    inline void set_viewport_scaling(const double x, const double y) { viewport_scaling = gfx::math::Vec2d { x, y }; }

    inline int get_transform_recalculation_count() { return scene_graph->get_transform_recalculation_count(); }

private:

    std::vector<std::pair<std::shared_ptr<Primitive2D>, gfx::math::Matrix3x3d>> get_draw_queue() const;

    std::shared_ptr<RenderSurface> surface;
    std::shared_ptr<SceneGraph2D> scene_graph;
    std::shared_ptr<gfx::text::FontManagerTTF> font_manager;

    std::vector<std::pair<std::shared_ptr<Primitive2D>, gfx::math::Matrix3x3d>> draw_queue;

    math::Vec2d viewport_scaling;
};

}

#endif // RENDER_2D_H
