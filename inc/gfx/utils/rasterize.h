#ifndef GFX_RASTERIZE_H
#define GFX_RASTERIZE_H

#include <gfx/core/render-surface.h>
#include <gfx/math/vec2.h>
#include <gfx/math/box2.h>
#include <gfx/math/obb2.h>

namespace gfx::utils
{

void rasterize_filled_polygon(std::shared_ptr<gfx::core::RenderSurface> surface, const std::vector<gfx::math::Vec2d> vertices, const gfx::core::types::Color3 color);
void rasterize_filled_triangle(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d v0, const gfx::math::Vec2d v1, const gfx::math::Vec2d v2, const gfx::core::types::Color3 color);

void rasterize_circle(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d center, const double radius, const gfx::core::types::Color3 color, const gfx::math::Vec2d scale = gfx::math::Vec2d { 1, 1 });
void rasterize_line(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d start, const gfx::math::Vec2d end, const double line_thickness, const gfx::core::types::Color3 color);
void rasterize_aabb(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Box2d bounds, const gfx::core::types::Color3 color);
void rasterize_obb(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::OBB2D obb, const gfx::core::types::Color3 color);
void rasterize_cross(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d pos, const double size, const gfx::core::types::Color3 color);

}

#endif // GFX_RASTERIZE_H
