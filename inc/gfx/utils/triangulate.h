#ifndef TRIANGULATE_H
#define TRIANGULATE_H

#include <vector>
#include <gfx/math/vec2.h>
#include <gfx/math/triangle-2D.h>

namespace gfx::utils
{

std::vector<gfx::math::Triangle> triangulate_polygon(const std::vector<gfx::math::Vec2d> &vertices, const bool clockwise);

}

#endif // TRIANGULATE_H
