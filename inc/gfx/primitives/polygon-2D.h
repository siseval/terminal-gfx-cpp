#ifndef POLYGON_2D_H
#define POLYGON_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>
#include <gfx/geometry/triangle.h>

namespace gfx::primitives
{

class Polygon2D : public gfx::core::Primitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const math::Matrix3x3d &transform) const override;
    gfx::math::Box2d get_geometry_size() const override;

    bool point_collides(const gfx::math::Vec2d point, const gfx::math::Matrix3x3d &transform) const override;

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


private:

    void rasterize_filled_triangle(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::geometry::Triangle &triangle) const;

    std::vector<gfx::math::Vec2d> points = std::vector<gfx::math::Vec2d>();
    bool clockwise = false;
    static constexpr int CORNER_SEGMENTS = 8;
};

};

#endif // POLYGON_2D_H
