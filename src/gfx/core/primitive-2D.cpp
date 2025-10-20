#include <gfx/core/primitive-2D.h>
#include <gfx/utils/transform.h>

namespace gfx::core
{

using namespace gfx::core::types;
using namespace gfx::math;

Box2d Primitive2D::get_axis_aligned_bounding_box(const Matrix3x3d &transform) const
{
    Box2d extent { get_geometry_size() };
    Vec2d top_left { extent.min };
    Vec2d bot_right { extent.max };

    std::vector<Vec2d> corners {
        { top_left.x, top_left.y },
        { bot_right.x, top_left.y },
        { top_left.x, bot_right.y },
        { bot_right.x, bot_right.y },
    };
    std::vector<Vec2d> transformed_corners { utils::transform_points(corners, transform) };

    Box2d bounds { transformed_corners[0], transformed_corners[0] };
    bounds.expand(transformed_corners);

    return bounds;
}

OBB2D Primitive2D::get_oriented_bounding_box(const Matrix3x3d &transform) const
{
    Box2d extent { get_geometry_size() };

    OBB2D bounds {
        extent.min,
        { extent.max.x - extent.min.x, 0 },
        { 0, extent.max.y - extent.min.y }
    };
   
    bounds.origin = utils::transform_point(bounds.origin, transform);
    bounds.side_x = utils::transform_vector(bounds.side_x, transform);
    bounds.side_y = utils::transform_vector(bounds.side_y, transform);

    return bounds;
}

Matrix3x3d Primitive2D::get_transform() const
{
    Vec2d size { get_geometry_size().size() };
    Vec2d anchor_offset { get_anchor() * size };

    Matrix3x3d anchor_translation_matrix { utils::translate(-anchor_offset) };
    Matrix3x3d scale_matrix { utils::scale(scale) };
    Matrix3x3d rotation_matrix { utils::rotate(rotation) };
    Matrix3x3d position_translation_matrix { utils::translate(get_position()) };

    return position_translation_matrix * rotation_matrix * scale_matrix * anchor_translation_matrix;
}

}


