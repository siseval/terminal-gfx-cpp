#ifndef POLYLINE_2D_H
#define POLYLINE_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/gfx-primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>

namespace gfx::primitives
{

class Polyline2D : public gfx::core::GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const math::Matrix3x3d transform) const override;
    // void update_bounds(std::shared_ptr<gfx_context> context) override;
    gfx::math::Box2d get_relative_extent() const override;

    inline void add_point(const gfx::math::Vec2d point) { points.push_back(point); }
    inline void add_points(const std::vector<gfx::math::Vec2d>& new_points) { points.insert(points.end(), new_points.begin(), new_points.end()); }
    inline void set_points(const std::vector<gfx::math::Vec2d>& new_points) { points = new_points; }
    inline void clear_points() { points.clear(); }

    inline const std::vector<gfx::math::Vec2d>& get_points() const { return points; }

    inline void set_close(const bool close) { do_close = close; }
    inline bool get_close() const { return do_close; }

protected:

    void rasterize_fill(std::shared_ptr<gfx::core::RenderSurface> surface, const math::Matrix3x3d transform) const;

    std::vector<gfx::math::Vec2d> points = std::vector<gfx::math::Vec2d>();
    bool do_close = false;
};

};

#endif // POLYLINE_2D_H
