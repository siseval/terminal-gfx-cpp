#ifndef GFX_PRIMITIVE_2D_H
#define GFX_PRIMITIVE_2D_H

#include "color3.h"
#include "curspp.h"
#include "gfx-context.h"
#include "matrix.h"

namespace curspp::graphics
{

struct bbox_2D
{
    coord2D min;
    coord2D max;
};

typedef std::vector<bool> raster_2D;

class GfxPrimitive2D
{

public:
        
    virtual void rasterize(std::shared_ptr<gfx_context> context) = 0;
    virtual void update_bounds(std::shared_ptr<gfx_context> context) = 0;

    Matrix3x3d get_transform(std::shared_ptr<gfx_context> context) const;
    Matrix3x3d invert_affine(Matrix3x3d m);

    inline Color3 get_color() const { return color; }
    inline void set_color(const Color3 col) { color = col; }

    inline bool get_draw_bounds() { return draw_bounds; }
    inline void set_draw_bounds(const bool draw) { draw_bounds = draw; }

    inline bool get_draw_anchor() { return draw_anchor; }
    inline void set_draw_anchor(const bool draw) { draw_anchor = draw; }

    inline bbox_2D get_bounds() const { return bounds; }

    inline Vec2f get_anchor() const { return anchor; }
    inline void set_anchor(const Vec2f pos) { anchor = pos; }

    inline coord2D get_pos() const { return bounds.min; }
    void set_pos(const coord2D pos);
    
    inline void set_pos_center(const coord2D pos) { set_pos(pos - get_size() / 2); }

    // inline void set_screen_pos_center(const std::shared_ptr<gfx_context> context, const vec2f pos) { vec2f foo = pos * context->resolution; set_pos_center(pos * (context->resolution / context->viewport_scaling)); }
    // inline void set_screen_pos(const std::shared_ptr<gfx_context> context, const vec2f pos) { set_pos(pos * context->resolution); }

    inline coord2D get_size() const { return bounds.max - bounds.min; }
    inline void set_size(const coord2D size) { bounds.max = bounds.min + size; }

    inline coord2D get_center() const { return (bounds.min + bounds.max) / 2; }

    inline Vec2f get_scale() const { return scale; }
    inline void set_scale(const Vec2f s) { scale = s; }

    inline double get_rotation() const { return rotation; }
    inline void set_rotation(const double r) { rotation = r; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double thickness) { line_thickness = thickness; }

protected:

    Color3 color;
    bbox_2D bounds;
    Vec2f anchor = { 0.0, 0.0 };
    Vec2f scale = { 1.0, 1.0 };
    double line_thickness = 1.0;
    double rotation = 0.0;
    bool draw_bounds = false;
    bool draw_anchor = false;

};

coord2D apply_transform(const Vec2d pos, const Matrix3x3d transform);
void rasterize_bounds(std::shared_ptr<gfx_context> context, const bbox_2D bounds);
void rasterize_anchor(std::shared_ptr<gfx_context> context, const coord2D pos);
void rasterize_line(std::shared_ptr<gfx_context> context, const coord2D start, const coord2D end, double line_thickness, const Color3 color);
void rasterize_circle(std::shared_ptr<gfx_context> context, const coord2D center, const double radius, const Color3 color);
Vec2d rotate_point(const coord2D point, const double angle);

};

#endif // GFX_PRIMITIVE_2D_H
