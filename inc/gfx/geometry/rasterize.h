#ifndef RASTERIZE_H
#define RASTERIZE_H

#include <gfx/core/render-surface.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>
#include <gfx/geometry/triangle.h>
#include <gfx/core/types/pixel.h>
#include <gfx/core/types/color4.h>

namespace gfx::geometry
{

void rasterize_filled_triangle(const Triangle &triangle, const core::types::Color4 color, const std::function<void(const gfx::core::types::Pixel&)> emit_pixel);


static constexpr int CORNER_SEGMENTS = 8;

}

#endif // RASTERIZE_H
