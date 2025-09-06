#ifndef ELLIPSE_2D_H
#define ELLIPSE_2D_H

#include "gfx-primitive-2D.h"

namespace curspp::graphics
{

class Ellipse2D : public GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx_context> context) const override;
    // void update_bounds(std::shared_ptr<gfx_context> context) override;
    BBox2D get_relative_extent() const override;

    inline Vec2d get_radius() const { return radius; }
    inline void set_radius(const Vec2d r) { radius = r; }

    inline bool get_fill() const { return draw_fill; }
    inline void set_fill(const bool fill) { draw_fill = fill; }

private:

    Vec2d radius;
    bool draw_fill = false;

};

};

#endif // ELLIPSE_2D_H
