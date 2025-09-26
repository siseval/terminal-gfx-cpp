#ifndef CIRCLE_2D_H
#define CIRCLE_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/gfx-primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/matrix.h>

namespace gfx::primitives
{

class Circle2D : public gfx::core::GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const override;
    gfx::math::Box2d get_relative_extent() const override;

    inline double get_radius() const { return radius; }
    inline void set_radius(const double r) { radius = r; }

private:

    double radius;
};

};

#endif // CIRCLE_2D_H
