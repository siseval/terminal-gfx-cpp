#ifndef ELLIPSE_2D_H
#define ELLIPSE_2D_H

#include "gfx-primitive-2D.h"

namespace curspp::graphics
{

class Ellipse2D : public GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx_context> context) override;
    void update_bounds() override;

    inline coord2D get_radius() const { return radius; }
    inline void set_radius(const coord2D r) { radius = r; update_bounds(); }

private:

    coord2D radius;

};

};

#endif // ELLIPSE_2D_H
