#include <gfx/utils/transform.h>

namespace gfx::utils
{

using namespace gfx::math;


Matrix3x3d translate(const Vec2d pos)
{
    return Matrix3x3d {
        { 1, 0, pos.x },
        { 0, 1, pos.y },
        { 0, 0, 1 }
    };
}

Matrix3x3d rotate(const double angle)
{
    double sin_angle { std::sin(angle) };
    double cos_angle { std::cos(angle) };

    return Matrix3x3d {
        { cos_angle, -sin_angle, 0 },
        { sin_angle, cos_angle, 0 },
        { 0, 0, 1 }
    };
}

Matrix3x3d scale(const Vec2d scale)
{
    return Matrix3x3d {
        { scale.x, 0, 0 },
        { 0, scale.y, 0 },
        { 0, 0, 1 }
    };
}

Vec2d extract_translation(const Matrix3x3d &transform)
{
    return Vec2d { transform(0, 2), transform(1, 2) };
}

double extract_rotation(const Matrix3x3d &transform)
{
    return std::atan2(transform(1, 0), transform(0, 0));
}

Vec2d extract_scale(const Matrix3x3d &transform)
{
    double scale_x { std::sqrt(transform(0, 0) * transform(0, 0) + transform(1, 0) * transform(1, 0)) };
    double scale_y { std::sqrt(transform(0, 1) * transform(0, 1) + transform(1, 1) * transform(1, 1)) };
    return Vec2d { scale_x, scale_y };
}

Vec2d transform_point(const Vec2d pos, const Matrix3x3d &transform)
{
    Matrix3x1d column_matrix {
        { pos.x }, 
        { pos.y }, 
        { 1 }};

    Matrix3x1d transformed { transform * column_matrix };
    return Vec2d { transformed(0, 0), transformed(1, 0), };
}

Vec2d transform_vector(const Vec2d vec, const Matrix3x3d &transform)
{
    Matrix3x1d column_matrix {
        { vec.x }, 
        { vec.y }, 
        { 0 }};

    Matrix3x1d transformed { transform * column_matrix };
    return Vec2d { transformed(0, 0), transformed(1, 0), };
}

std::vector<Vec2d> transform_points(const std::vector<Vec2d> points, const Matrix3x3d &transform)
{
    std::vector<Vec2d> transformed_points;
    for (auto point : points)
    {
        transformed_points.push_back(transform_point(point, transform));
    }
    return transformed_points;
}

std::vector<Vec2d> transform_vectors(const std::vector<Vec2d> vectors, const Matrix3x3d &transform)
{
    std::vector<Vec2d> transformed_vectors;
    for (auto vec : vectors)
    {
        transformed_vectors.push_back(transform_vector(vec, transform));
    }
    return transformed_vectors;
}

Matrix3x3d invert_affine(const Matrix3x3d &m)
{
    double a { m(0, 0) }, b { m(0, 1) }, c { m(0, 2) };
    double d { m(1, 0) }, e { m(1, 1) }, f { m(1, 2) };
    double det { a * e - b * d };

    if (det == 0) 
    {
        throw std::runtime_error("Matrix is not invertible");
    }

    double inv_det { 1.0 / det };

    Matrix3x3d inv;
    inv(0, 0) = e * inv_det;
    inv(0, 1) = -b * inv_det;
    inv(0, 2) = (b * f - c * e) * inv_det;
    inv(1, 0) = -d * inv_det;
    inv(1, 1) = a * inv_det;
    inv(1, 2) = (c * d - a * f) * inv_det;
    inv(2, 0) = 0;
    inv(2, 1) = 0;
    inv(2, 2) = 1;

    return inv;
}

}
