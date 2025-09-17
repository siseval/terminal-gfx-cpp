#ifndef GFX_PRIMITIVE_2D_H
#define GFX_PRIMITIVE_2D_H

#include <gfx/core/types/color3.h>
#include <gfx/utils/rasterize.h>
#include <gfx/utils/transform.h>
#include <gfx/math/box2.h>
#include <gfx/math/matrix.h>

namespace gfx::core
{

class GfxPrimitive2D
{

public:
        
    virtual void rasterize(std::shared_ptr<RenderSurface> surface, const gfx::math::Matrix3x3d transform) const = 0;

    gfx::math::Box2d get_axis_aligned_bounding_box(const gfx::math::Matrix3x3d transform) const;
    virtual gfx::math::Box2d get_relative_extent() const = 0;

    gfx::math::Matrix3x3d get_transform() const;

    inline types::Color3 get_color() const { return color; }
    inline void set_color(const types::Color3 col) { color = col; }

    inline bool get_draw_bounds() const { return draw_bounds; }
    inline void set_draw_bounds(const bool draw) { draw_bounds = draw; }

    inline bool get_draw_anchor() const { return draw_anchor; }
    inline void set_draw_anchor(const bool draw) { draw_anchor = draw; }

    inline gfx::math::Box2d get_bounds() const { return bounds; }
    inline gfx::math::Vec2d get_bounds_size() const { return bounds.size(); }

    inline gfx::math::Vec2d get_anchor() const { return anchor; }
    inline void set_anchor(const gfx::math::Vec2d pos) { anchor = pos; }

    inline void set_depth(const int d) { depth = d; }
    inline int get_depth() const { return depth; }

    inline gfx::math::Vec2d get_pos() const { return position; }
    void set_pos(const gfx::math::Vec2d pos) { position = pos; }
    
    // inline gfx::math::Vec2d get_size() const { return bounds.max - bounds.min; }
    // inline void set_size(const gfx::math::Vec2d size) { bounds.max = bounds.min + size; }

    // inline gfx::math::Vec2d get_center() const { return (bounds.min + bounds.max) / 2; }

    inline gfx::math::Vec2f get_scale() const { return scale; }
    inline void set_scale(const gfx::math::Vec2d s) { scale = s; }

    inline double get_rotation() const { return rotation; }
    inline void set_rotation(const double r) { rotation = r; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double thickness) { line_thickness = thickness; }

    inline double get_fill() const { return fill; }
    inline void set_fill(const double f) { fill = f; }

protected:

    types::Color3 color;
    gfx::math::Box2d bounds;
    gfx::math::Vec2d position;
    gfx::math::Vec2d anchor = { 0.0, 0.0 };
    gfx::math::Vec2d scale = { 1.0, 1.0 };
    double line_thickness = 1.0;
    double fill = 0;
    double rotation = 0.0;
    int depth = 0;
    bool draw_bounds = false;
    bool draw_anchor = false;

    // bool should_fill_pixel(std::shared_ptr<GfxContext2D> context, const gfx::math::Vec2d pixel) const;

};


};

#endif // GFX_PRIMITIVE_2D_H
