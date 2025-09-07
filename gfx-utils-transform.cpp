#include "gfx-utils-transform.h"

namespace curspp::gfx::utils
{

Matrix3x3d translate(const Vec2d pos)
{
    return Matrix3x3d({
        { 1, 0, pos.x },
        { 0, 1, pos.y },
        { 0, 0, 1 }
    });
}

Matrix3x3d rotate(const double angle)
{
    double sin_angle = std::sin(angle);
    double cos_angle = std::cos(angle);
    return Matrix3x3d({
        { cos_angle, -sin_angle, 0 },
        { sin_angle, cos_angle, 0 },
        { 0, 0, 1 }
    });
}

Matrix3x3d scale(const Vec2d scale)
{
    return Matrix3x3d({
        { scale.x, 0, 0 },
        { 0, scale.y, 0 },
        { 0, 0, 1 }
    });
}


}
