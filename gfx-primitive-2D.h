#ifndef GFX_PRIMITIVE_2D_H
#define GFX_PRIMITIVE_2D_H

#include "color3.h"
#include "box2.h"
#include "curspp.h"
#include "gfx-context-2D.h"
#include "gfx-rasterize.h"
#include "matrix.h"

namespace curspp::graphics
{

class GfxPrimitive2D
{

public:
        
    virtual void rasterize(std::shared_ptr<GfxContext2D> context) const = 0;
    void rasterize_bounds(std::shared_ptr<GfxContext2D> context) const;
    void rasterize_anchor(std::shared_ptr<GfxContext2D> context) const;

    Box2d get_global_bounds(std::shared_ptr<GfxContext2D> context) const;
    virtual Box2d get_relative_extent() const = 0;

    Matrix3x3d get_transform() const;

    inline Color3 get_color() const { return color; }
    inline void set_color(const Color3 col) { color = col; }

    inline bool get_draw_bounds() const { return draw_bounds; }
    inline void set_draw_bounds(const bool draw) { draw_bounds = draw; }

    inline bool get_draw_anchor() const { return draw_anchor; }
    inline void set_draw_anchor(const bool draw) { draw_anchor = draw; }

    inline Box2d get_bounds() const { return bounds; }
    inline Vec2d get_bounds_size() const { return bounds.size(); }

    inline Vec2d get_anchor() const { return anchor; }
    inline void set_anchor(const Vec2d pos) { anchor = pos; }

    inline void set_depth(const int d) { depth = d; }
    inline int get_depth() const { return depth; }

    inline Vec2d get_pos() const { return position; }
    void set_pos(const Vec2d pos) { position = pos; }
    
    // inline Vec2d get_size() const { return bounds.max - bounds.min; }
    // inline void set_size(const Vec2d size) { bounds.max = bounds.min + size; }

    // inline Vec2d get_center() const { return (bounds.min + bounds.max) / 2; }

    inline Vec2f get_scale() const { return scale; }
    inline void set_scale(const Vec2d s) { scale = s; }

    inline double get_rotation() const { return rotation; }
    inline void set_rotation(const double r) { rotation = r; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double thickness) { line_thickness = thickness; }

protected:

    Color3 color;
    Box2d bounds;
    Vec2d position;
    Vec2d anchor = { 0.0, 0.0 };
    Vec2d scale = { 1.0, 1.0 };
    double line_thickness = 1.0;
    double rotation = 0.0;
    int depth = 0;
    bool draw_bounds = false;
    bool draw_anchor = false;

};

Vec2d apply_transform(const Vec2d pos, const Matrix3x3d transform);
Matrix3x3d invert_affine(Matrix3x3d m);

};

#endif // GFX_PRIMITIVE_2D_H
