#ifndef POLYLINE_2D_H
#define POLYLINE_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/gfx-primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>
#include <gfx/geometry/triangle.h>

namespace gfx::primitives
{

class Polyline2D : public gfx::core::GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const math::Matrix3x3d &transform) const override;
    gfx::math::Box2d get_relative_extent() const override;

    bool cache_clockwise();

    inline void add_point(const gfx::math::Vec2d point) { points.push_back(point); cache_clockwise(); }
    inline void add_points(const std::vector<gfx::math::Vec2d> &new_points) { points.insert(points.end(), new_points.begin(), new_points.end()); cache_clockwise(); }

    inline void set_point(const size_t index, const gfx::math::Vec2d point) 
    { 
        if (index < points.size()) 
        { 
            points[index] = point; 
            cache_clockwise();
        } 
    }
    inline void set_points(const std::vector<gfx::math::Vec2d> &new_points) { points = new_points; cache_clockwise(); }
    inline void clear_points() { points.clear(); }

    inline const std::vector<gfx::math::Vec2d> get_points() const { return points; }

    inline void set_close(const bool close) { do_close = close; }
    inline bool get_close() const { return do_close; }

    inline void set_rounded_corners(const bool rounded) { do_rounded_corners = rounded; }
    inline bool get_rounded_corners() const { return do_rounded_corners; }


private:

    void rasterize_filled_triangle(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::geometry::Triangle &triangle) const;
    void rasterize_rounded_corners(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const;
    void rasterize_rounded_corner(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d pos, const double angle0, const double angle1, const gfx::math::Matrix3x3d &transform) const;
    void rasterize_edge(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d start, const gfx::math::Vec2d end, const gfx::math::Matrix3x3d &transform) const;

    std::vector<gfx::math::Vec2d> points = std::vector<gfx::math::Vec2d>();
    bool do_close = false;
    bool do_rounded_corners = false;
    bool clockwise = false;
    static constexpr int CORNER_SEGMENTS = 8;
};

};

#endif // POLYLINE_2D_H
