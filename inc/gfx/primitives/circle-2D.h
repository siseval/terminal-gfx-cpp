#ifndef CIRCLE_2D_H
#define CIRCLE_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/matrix.h>

namespace gfx::primitives
{

class Circle2D : public gfx::core::Primitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const override;
    gfx::math::Box2d get_geometry_size() const override;
    gfx::math::Box2d get_axis_aligned_bounding_box(const gfx::math::Matrix3x3d &transform) const override;

    bool point_collides(const gfx::math::Vec2d point, const gfx::math::Matrix3x3d &transform) const override;

    inline double get_radius() const { return radius; }
    inline void set_radius(const double r) { radius = r; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double t) { line_thickness = t; }

    inline bool get_filled() const { return filled; }
    inline void set_filled(const bool f) { filled = f; }

private:

    double radius;
    bool filled = false;
    double line_thickness = 1.0;

};

};

#endif // CIRCLE_2D_H
