#ifndef GFX_PRIMITIVE_2D_H
#define GFX_PRIMITIVE_2D_H

#include <gfx/core/types/color4.h>
#include <gfx/utils/uuid.h>
#include <gfx/utils/rasterize.h>
#include <gfx/utils/transform.h>
#include <gfx/math/box2.h>
#include <gfx/math/matrix.h>
#include <gfx/math/obb-2D.h>

namespace gfx::core
{

class GfxPrimitive2D
{

public:

    GfxPrimitive2D() : id(gfx::utils::UUID::generate()) {}
        
    virtual void rasterize(std::shared_ptr<RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const = 0;

    gfx::math::Box2d get_axis_aligned_bounding_box(const gfx::math::Matrix3x3d &transform) const;
    gfx::math::OBB2D get_oriented_bounding_box(const gfx::math::Matrix3x3d &transform) const;
    virtual gfx::math::Box2d get_relative_extent() const = 0;

    gfx::math::Matrix3x3d get_transform() const;

    inline gfx::utils::UUID get_id() const { return id; }

    inline types::Color4 get_color() const { return color; }
    inline void set_color(const types::Color4 col) { color = col; }

    inline bool get_draw_aabb() const { return draw_aabb; }
    inline void set_draw_aabb(const bool draw) { draw_aabb = draw; }

    inline bool get_draw_anchor() const { return draw_anchor; }
    inline void set_draw_anchor(const bool draw) { draw_anchor = draw; }

    inline bool get_draw_obb() const { return draw_obb; }
    inline void set_draw_obb(const bool draw) { draw_obb = draw; }

    inline gfx::math::Box2d get_bounds() const { return bounds; }
    inline gfx::math::Vec2d get_bounds_size() const { return bounds.size(); }

    inline gfx::math::Vec2d get_anchor() const { return anchor; }
    inline void set_anchor(const gfx::math::Vec2d pos) { anchor = pos; }

    inline void set_depth(const int d) { depth = d; }
    inline int get_depth() const { return depth; }

    inline gfx::math::Vec2d get_pos() const { return position; }
    void set_pos(const gfx::math::Vec2d pos) { position = pos; }
    
    inline gfx::math::Vec2f get_scale() const { return scale; }
    inline void set_scale(const gfx::math::Vec2d s) { scale = s; }
    inline void set_scale(const double s) { scale = gfx::math::Vec2d { s, s }; }

    inline double get_rotation() const { return rotation; }
    inline void set_rotation(const double r) { rotation = r; }

    inline double get_line_thickness() const { return line_thickness; }
    inline void set_line_thickness(const double thickness) { line_thickness = thickness; }

    inline bool get_fill() const { return fill; }
    inline void set_fill(const bool f) { fill = f; }

    inline bool is_visible() const { return visible; }
    inline void set_visible(const bool v) { visible = v; }

protected:

    gfx::utils::UUID id;

    types::Color4 color;

    gfx::math::Box2d bounds;
    gfx::math::Vec2d position;
    gfx::math::Vec2d anchor = { 0.0, 0.0 };
    gfx::math::Vec2d scale = { 1.0, 1.0 };

    double line_thickness = 1.0;
    bool fill = false;
    bool visible = true;
    double rotation = 0.0;
    int depth = 0;
    bool draw_aabb = false;
    bool draw_obb = false;
    bool draw_anchor = false;

    // bool should_fill_pixel(std::shared_ptr<GfxContext2D> context, const gfx::math::Vec2d pixel) const;

};

};

template <>
struct std::hash<gfx::core::GfxPrimitive2D>
{
    size_t operator()(const gfx::core::GfxPrimitive2D& item) const
    {
        int64_t hash = std::hash<gfx::math::Vec2d>()(item.get_pos());
        hash ^= (std::hash<gfx::math::Vec2d>()(item.get_scale()) << 1);
        hash ^= (std::hash<double>()(item.get_rotation()) << 1);
        hash ^= (std::hash<int>()(item.get_depth()) << 1);

        return hash;
    }
};


#endif // GFX_PRIMITIVE_2D_H
