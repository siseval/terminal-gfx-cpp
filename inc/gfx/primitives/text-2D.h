#ifndef TEXT_2D_H
#define TEXT_2D_H

#include <string>
#include <gfx/core/gfx-primitive-2D.h>
#include <gfx/text/font-ttf.h>

namespace gfx::primitives
{

class Text2D : public gfx::core::GfxPrimitive2D
{
    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const override;
    gfx::math::Box2d get_relative_extent() const override;

private:

    std::string text;
    std::shared_ptr<gfx::text::FontTTF> font;
};

}

#endif // TEXT_2D_H
