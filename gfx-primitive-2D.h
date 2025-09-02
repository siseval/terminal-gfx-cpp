#ifndef GFX_PRIMITIVE_2D_H
#define GFX_PRIMITIVE_2D_H

#include "color3.h"
#include "curspp.h"
#include "gfx-context.h"

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
    virtual void update_bounds() = 0;

    inline Color3 get_color() const { return color; }
    inline void set_color(const Color3 col) { color = col; }

    inline bool get_draw_bounds() { return draw_bounds; }
    inline void set_draw_bounds(const bool draw) { draw_bounds = draw; }

    inline bbox_2D get_bounds() const { return bounds; }
    inline void set_bounds(const bbox_2D box) { bounds = box; }

    inline coord2D get_anchor() const { return anchor; }
    inline void set_anchor(const coord2D pos) { anchor = pos; }

    inline coord2D get_pos() const { return bounds.min; }
    void set_pos(const coord2D pos);
    
    inline void set_pos_center(const coord2D pos) { set_pos(pos - get_size() / 2); }

    // inline void set_screen_pos_center(const std::shared_ptr<gfx_context> context, const vec2f pos) { vec2f foo = pos * context->resolution; set_pos_center(pos * (context->resolution / context->viewport_scaling)); }
    // inline void set_screen_pos(const std::shared_ptr<gfx_context> context, const vec2f pos) { set_pos(pos * context->resolution); }

    inline coord2D get_size() const { return bounds.max - bounds.min; }

    inline coord2D get_center() const { return (bounds.min + bounds.max) / 2; }

    inline double get_rotation() const { return rotation; }
    inline void set_rotation(const double r) { rotation = r; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double thickness) { line_thickness = thickness; update_bounds(); }

protected:

    Color3 color;
    bbox_2D bounds;
    coord2D anchor;
    double line_thickness;
    double rotation = 0.0;
    bool draw_bounds = false;

    void rasterize_bounds(std::shared_ptr<gfx_context> context);
};

void rasterize_line(std::shared_ptr<gfx_context> context, const coord2D start, const coord2D end, double line_thickness, const Color3 color);
void rasterize_circle(std::shared_ptr<gfx_context> context, const coord2D center, const double radius, const Color3 color);
vec2d rotate_point(const coord2D point, const double angle);

};

#endif // GFX_PRIMITIVE_2D_H
