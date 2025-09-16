#include <gfx/core/gfx-primitive-2D.h>

namespace gfx::core
{

using namespace gfx::math;

Box2d GfxPrimitive2D::get_axis_aligned_bounding_box(const Matrix3x3d transform) const
{
    Box2d extent = get_relative_extent();
    Vec2d top_left = extent.min - Vec2d::create(std::ceil(get_line_thickness() / 2));
    Vec2d bot_right = extent.max + Vec2d::create(std::ceil(get_line_thickness() / 2));

    std::vector<Vec2d> corners = {
         Vec2d { top_left.x, top_left.y },
         Vec2d { bot_right.x, top_left.y },
         Vec2d { top_left.x,  bot_right.y },
         Vec2d { bot_right.x,  bot_right.y },
    };
    std::vector<Vec2d> transformed_corners = utils::apply_transform(corners, transform);

    Box2d bounds = Box2d { transformed_corners[0], transformed_corners[0] };
    bounds.expand(transformed_corners);

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

}


