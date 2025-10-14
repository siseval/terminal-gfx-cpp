#ifndef FLATTEN_H
#define FLATTEN_H

#include <vector>
#include <gfx/math/vec2.h>

namespace gfx::geometry
{

std::vector<gfx::math::Vec2d> flatten_bezier(const gfx::math::Vec2d p0, const gfx::math::Vec2d p1, const gfx::math::Vec2d p2, const double tolerance = 0.5);
std::vector<gfx::math::Vec2d> flatten_contour(const std::vector<std::pair<gfx::math::Vec2d, bool>> &points_on_off_curve);

}

#endif // FLATTEN_H
