#ifndef ELLIPSE_2D_H
#define ELLIPSE_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>

namespace gfx::primitives
{

class Ellipse2D : public gfx::core::Primitive2D
{

public:

    void rasterize(const gfx::math::Matrix3x3d &transform, const std::function<void(const gfx::core::types::Pixel&)> emit_pixel) const override;
    gfx::math::Box2d get_geometry_size() const override;
    gfx::math::Box2d get_axis_aligned_bounding_box(const gfx::math::Matrix3x3d &transform) const override;

    bool point_collides(const gfx::math::Vec2d point, const gfx::math::Matrix3x3d &transform) const override;

    inline gfx::math::Vec2d get_radius() const { return radius; }
    inline void set_radius(const gfx::math::Vec2d r) { radius = r; }
    inline void set_radius(const double rx, const double ry) { radius = gfx::math::Vec2d { rx, ry }; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double t) { line_thickness = t; }

    inline bool get_filled() const { return filled; }
    inline void set_filled(const bool f) { filled = f; }

private:

    gfx::math::Vec2d radius;
    double line_thickness = 1.0;
    bool filled = false;
    
    double MIN_MULTITHREAD_PIXELS { 100 * 100 };
};

};

#endif // ELLIPSE_2D_H
