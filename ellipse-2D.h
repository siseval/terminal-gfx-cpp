#ifndef ELLIPSE_2D_H
#define ELLIPSE_2D_H

#include "gfx-primitive-2D.h"

namespace curspp::gfx
{

class Ellipse2D : public GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<GfxContext2D> context) const override;
    // void update_bounds(std::shared_ptr<gfx_context> context) override;
    Box2d get_relative_extent() const override;

    inline Vec2d get_radius() const { return radius; }
    inline void set_radius(const Vec2d r) { radius = r; }

private:

    Vec2d radius;

};

};

#endif // ELLIPSE_2D_H
