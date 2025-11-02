#ifndef TEXT_2D_H
#define TEXT_2D_H

#include <string>
#include <gfx/core/primitive-2D.h>
#include <gfx/text/font-ttf.h>

namespace gfx::primitives
{

class Text2D : public gfx::core::Primitive2D
{
    void rasterize(const gfx::math::Matrix3x3d &transform, const std::function<void(const gfx::core::types::Pixel&)> emit_pixel) const override;
    gfx::math::Box2d get_geometry_size() const override;

private:

    std::string text;
    std::shared_ptr<gfx::text::FontTTF> font;
};

}

#endif // TEXT_2D_H
