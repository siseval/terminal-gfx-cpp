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
    inline void set_color(const Color3 c) { color = c; }

    inline bbox_2D get_bounds() const { return bounds; }
    inline void set_bounds(const bbox_2D b) { bounds = b; }

    inline coord2D get_position() const { return bounds.min; }
    inline void set_position(const coord2D pos) 
    { 
        coord2D size = bounds.max - bounds.min;
        bounds.min = pos; 
        bounds.max = pos + size;
        update_bounds();
    }
    inline void set_center_position(const coord2D pos) 
    { 
        set_position(pos - get_size() / 2);
    }
    

    inline coord2D get_size() const { return bounds.max - bounds.min; }

    inline coord2D get_center() const { return (bounds.min + bounds.max) / 2; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double thickness) { line_thickness = thickness; update_bounds(); }

private:

    Color3 color;
    bbox_2D bounds;
    double line_thickness;
};

};

#endif // GFX_PRIMITIVE_2D_H
