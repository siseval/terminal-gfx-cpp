#ifndef GFX_RASTERIZE_H
#define GFX_RASTERIZE_H

#include <gfx/core/render-surface.h>
#include <gfx/math/vec2.h>
#include <gfx/math/box2.h>

namespace gfx::utils
{

void rasterize_circle(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d center, const double radius, const gfx::core::types::Color3 color, const gfx::math::Vec2d scale = gfx::math::Vec2d { 1, 1 });
void rasterize_line(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d start, const gfx::math::Vec2d end, const double line_thickness, const gfx::core::types::Color3 color);
void rasterize_box_corners(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Box2d bounds);
void rasterize_point(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d pos);

}

#endif // GFX_RASTERIZE_H
