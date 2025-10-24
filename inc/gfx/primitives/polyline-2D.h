#ifndef POLYLINE_2D_H
#define POLYLINE_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/primitive-2D.h>
#include <gfx/math/box2.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>
#include <gfx/geometry/triangle.h>

namespace gfx::primitives
{

class Polyline2D : public gfx::core::Primitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const math::Matrix3x3d &transform) const override;
    gfx::math::Box2d get_geometry_size() const override;
    gfx::math::Box2d get_axis_aligned_bounding_box(const gfx::math::Matrix3x3d &transform) const override;

    bool point_collides(const gfx::math::Vec2d point, const gfx::math::Matrix3x3d &transform) const override;

    bool cache_clockwise();

    inline void add_point(const gfx::math::Vec2d point) { points.push_back(point); cache_clockwise(); }
    inline void add_point(const double x, const double y) { points.push_back(gfx::math::Vec2d { x, y }); cache_clockwise(); }
    inline void add_points(const std::vector<gfx::math::Vec2d> &new_points) { points.insert(points.end(), new_points.begin(), new_points.end()); cache_clockwise(); }

    inline void set_point(const size_t index, const gfx::math::Vec2d point) 
    { 
        if (index < points.size()) 
        { 
            points[index] = point; 
            cache_clockwise();
        } 
    }
    inline void set_point(const size_t index, const double x, const double y) 
    { 
        if (index < points.size()) 
        { 
            points[index] = gfx::math::Vec2d { x, y }; 
            cache_clockwise();
        } 
    }
    inline void set_points(const std::vector<gfx::math::Vec2d> &new_points) { points = new_points; cache_clockwise(); }
    inline void clear_points() { points.clear(); }

    inline void set_segment_visible(const size_t index, const bool visible) 
    { 
        if (segments_visible.size() < points.size()) 
        { 
            segments_visible.resize(points.size(), true); 
        }
        if (index < points.size()) 
        { 
            segments_visible[index] = visible; 
        } 
    }
    inline bool get_segment_visible(const size_t index) const 
    { 
        if (index < points.size()) 
        { 
            return segments_visible[index]; 
        } 
        return false; 
    }

    inline const std::vector<gfx::math::Vec2d> get_points() const { return points; }
    inline gfx::math::Vec2d get_point(const size_t index) const 
    { 
        if (index < points.size()) 
        { 
            return points[index]; 
        } 
        return gfx::math::Vec2d::zero(); 
    }

    inline size_t get_num_points() const { return points.size(); }

    inline void set_close(const bool close) { do_close = close; }
    inline bool get_close() const { return do_close; }

    inline void set_rounded_corners(const bool rounded) { do_rounded_corners = rounded; }
    inline bool get_rounded_corners() const { return do_rounded_corners; }

    inline void set_line_thickness(const double t) { line_thickness = t; }
    inline double get_line_thickness() const { return line_thickness; }

    inline bool get_fill() const { return filled; }
    inline void set_fill(const bool f) { filled = f; }

private:

    void rasterize_filled_triangle(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::geometry::Triangle &triangle) const;
    void rasterize_rounded_corners(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const;
    void rasterize_rounded_corner(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d pos, const double angle0, const double angle1, const gfx::math::Matrix3x3d &transform) const;
    void rasterize_edge(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d start, const gfx::math::Vec2d end, const gfx::math::Matrix3x3d &transform) const;

    std::vector<gfx::math::Vec2d> points;
    std::vector<bool> segments_visible;
    bool do_close = false;
    bool filled = false;
    double line_thickness = 1.0;
    bool do_rounded_corners = false;
    bool clockwise = false;
    static constexpr int CORNER_SEGMENTS = 8;
};

};

#endif // POLYLINE_2D_H
