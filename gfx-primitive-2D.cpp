#include "gfx-primitive-2D.h"

namespace curspp::gfx
{

void GfxPrimitive2D::rasterize_bounds(std::shared_ptr<GfxContext2D> context) const
{
    Box2d bounds = get_global_bounds(context);
    utils::rasterize_box_corners(context, Box2d { { bounds.min }, { bounds.max } });
}

void GfxPrimitive2D::rasterize_anchor(std::shared_ptr<GfxContext2D> context) const
{
    Matrix3x3d full_transform = context->get_transform() * get_transform();
    utils::rasterize_point(context, apply_transform(get_anchor() * get_relative_extent().size(), full_transform));
}

Box2d GfxPrimitive2D::get_global_bounds(std::shared_ptr<GfxContext2D> context) const
{
    Matrix3x3d full_transform = context->get_transform() * get_transform();

    Box2d extent = get_relative_extent();
    Vec2d top_left = extent.min - Vec2d::create(std::ceil(get_line_thickness() / 2));
    Vec2d bot_right = extent.max + Vec2d::create(std::ceil(get_line_thickness() / 2));

    Vec2d corners[4] = {
         Vec2d { top_left.x, top_left.y },
         Vec2d { bot_right.x, top_left.y },
         Vec2d { top_left.x,  bot_right.y },
         Vec2d { bot_right.x,  bot_right.y },
    };

    for (int i = 0; i < 4; ++i)
    {
        corners[i] = apply_transform(corners[i], full_transform);
    }

    Box2d bounds = { { corners[0].x, corners[0].y }, { corners[0].x, corners[0].y } };

    for (int i = 0; i < 4; ++i)
    {
        bounds.expand(corners[i]);
    }

    return bounds;
}

Matrix3x3d GfxPrimitive2D::get_transform() const
{
    Vec2d size = get_relative_extent().size();
    Vec2d anchor_offset = get_anchor() * size;

    Matrix3x3d anchor_translation_matrix = utils::translate(-anchor_offset);
    Matrix3x3d scale_matrix = utils::scale(scale);
    Matrix3x3d rotation_matrix  = utils::rotate(rotation);
    Matrix3x3d position_translation_matrix = utils::translate(get_pos());

    return position_translation_matrix * rotation_matrix * scale_matrix * anchor_translation_matrix;
}


Matrix3x3d invert_affine(Matrix3x3d m)
{
    double a = m(0, 0), b = m(0, 1), c = m(0, 2);
    double d = m(1, 0), e = m(1, 1), f = m(1, 2);
    double det = a * e - b * d;

    if (det == 0) 
    {
        throw std::runtime_error("Matrix is not invertible");
    }

    double inv_det = 1.0 / det;

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

Vec2d apply_transform(const Vec2d pos, const Matrix3x3d transform)
{
    Matrix3x1d column_matrix = Matrix3x1d({ 
        { pos.x }, 
        { pos.y }, 
        { 1 }});

    Matrix3x1d transformed = transform * column_matrix;
    return Vec2d { transformed(0, 0), transformed(1, 0), };
}


}


