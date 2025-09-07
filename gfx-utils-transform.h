#ifndef GFX_UTILS_TRANSFORM_H
#define GFX_UTILS_TRANSFORM_H

#include "matrix.h"
#include "vec2.h"

namespace curspp::gfx::utils
{

Matrix3x3d translate(const Vec2d pos);
Matrix3x3d rotate(const double angle);
Matrix3x3d scale(const Vec2d scale);

}

#endif // GFX_UTILS_TRANSFORM_H
