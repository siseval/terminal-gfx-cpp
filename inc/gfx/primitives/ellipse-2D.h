#ifndef ELLIPSE_2D_H
#define ELLIPSE_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/gfx-primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>

namespace gfx::primitives
{

class Ellipse2D : public gfx::core::GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const math::Matrix3x3d transform) const override;
    gfx::math::Box2d get_relative_extent() const override;

    inline gfx::math::Vec2d get_radius() const { return radius; }
    inline void set_radius(const gfx::math::Vec2d r) { radius = r; }

private:

    gfx::math::Vec2d radius;
    static constexpr int SEGMENTS = 64;
};

};

#endif // ELLIPSE_2D_H
