#include <gfx/core/gfx-primitive-2D.h>

namespace gfx::core
{

using namespace gfx::math;


void GfxPrimitive2D::rasterize_bounds(std::shared_ptr<GfxContext2D> context) const
{
    Box2d bounds = get_global_bounds(context);
    utils::rasterize_box_corners(context, Box2d { { bounds.min }, { bounds.max } });
}

void GfxPrimitive2D::rasterize_anchor(std::shared_ptr<GfxContext2D> context) const
{
    Matrix3x3d full_transform = context->get_transform() * get_transform();
    utils::rasterize_point(context, utils::apply_transform(get_anchor() * get_relative_extent().size(), full_transform));
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
        corners[i] = utils::apply_transform(corners[i], full_transform);
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


bool GfxPrimitive2D::should_fill_pixel(std::shared_ptr<GfxContext2D> context, const Vec2d pixel) const
{
    double fill = std::clamp(get_fill(), 0.0, 1.0);

    if (fill >= 1.0 - std::numeric_limits<double>::epsilon())
        return true;

    else return false;

    // bool on_checkerboard = (rounded_pos.x / gaps.x + rounded_pos.y / gaps.y) % 2 == 0;
}


}


