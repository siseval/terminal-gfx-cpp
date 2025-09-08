#ifndef GFX_UTILS_TRANSFORM_H
#define GFX_UTILS_TRANSFORM_H

#include "matrix.h"
#include "vec2.h"

namespace curspp::gfx::utils
{

Matrix3x3d translate(const Vec2d pos);
Matrix3x3d rotate(const double angle);
Matrix3x3d scale(const Vec2d scale);

Vec2d apply_transform(const Vec2d pos, const Matrix3x3d transform);
Matrix3x3d invert_affine(Matrix3x3d m);

}

#endif // GFX_UTILS_TRANSFORM_H
