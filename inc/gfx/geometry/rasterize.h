#ifndef RASTERIZE_H
#define RASTERIZE_H

#include <memory>
#include <gfx/core/render-surface.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>
#include <gfx/geometry/triangle.h>

namespace gfx::geometry
{

void rasterize_filled_triangle(std::shared_ptr<gfx::core::RenderSurface> surface, const Triangle &triangle, const gfx::core::types::Color4 color, const int depth);
void rasterize_rounded_corners(std::shared_ptr<gfx::core::RenderSurface> surface, const std::vector<gfx::math::Vec2d> &points, const double line_thickness, const gfx::core::types::Color4 color, const int depth);
void rasterize_rounded_corner(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d pos, const double angle0, const double angle1, const double line_thickness, const gfx::core::types::Color4 color, const int depth);
void rasterize_edge(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Vec2d start, const gfx::math::Vec2d end, const double line_thickness, const gfx::core::types::Color4 color, const int depth);


static constexpr int CORNER_SEGMENTS = 8;

}

#endif // RASTERIZE_H
