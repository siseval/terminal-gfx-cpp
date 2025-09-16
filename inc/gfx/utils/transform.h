#ifndef GFX_UTILS_TRANSFORM_H
#define GFX_UTILS_TRANSFORM_H

#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>

namespace gfx::utils
{

gfx::math::Matrix3x3d translate(const gfx::math::Vec2d pos);
gfx::math::Matrix3x3d rotate(const double angle);
gfx::math::Matrix3x3d scale(const gfx::math::Vec2d scale);

gfx::math::Vec2d extract_translation(const gfx::math::Matrix3x3d transform);
double extract_rotation(const gfx::math::Matrix3x3d transform);
gfx::math::Vec2d extract_scale(const gfx::math::Matrix3x3d transform);

gfx::math::Vec2d apply_transform(const gfx::math::Vec2d pos, const gfx::math::Matrix3x3d transform);
std::vector<gfx::math::Vec2d> apply_transform(const std::vector<gfx::math::Vec2d> points, const gfx::math::Matrix3x3d transform);

gfx::math::Matrix3x3d invert_affine(gfx::math::Matrix3x3d m);

}

#endif // GFX_UTILS_TRANSFORM_H
