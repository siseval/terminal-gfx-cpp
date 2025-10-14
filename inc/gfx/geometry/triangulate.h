#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include <vector>
#include <gfx/math/vec2.h>
#include <gfx/geometry/triangle.h>

namespace gfx::geometry
{

std::vector<Triangle> triangulate_polygon(const std::vector<gfx::math::Vec2d> &vertices, const bool clockwise);

}

#endif // TRIANGULATE_H
