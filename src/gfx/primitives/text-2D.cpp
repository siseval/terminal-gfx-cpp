#include <gfx/primitives/text-2D.h>

namespace gfx::primitives
{

using namespace gfx::math;

Box2d Text2D::get_relative_extent() const
{
    return gfx::math::Box2d { gfx::math::Vec2d { 0, 0 }, gfx::math::Vec2d { 0, 0 } };
}

void Text2D::rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const
{
}

}
