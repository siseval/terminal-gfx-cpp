#include <gfx/primitives/text-2D.h>

namespace gfx::primitives
{

using namespace gfx::math;
using namespace gfx::core::types;

Box2d Text2D::get_geometry_size() const
{
    return gfx::math::Box2d { gfx::math::Vec2d { 0, 0 }, gfx::math::Vec2d { 0, 0 } };
}

void Text2D::rasterize(const Matrix3x3d &transform, const std::function<void(const Pixel&)> emit_pixel) const
{
}

}
