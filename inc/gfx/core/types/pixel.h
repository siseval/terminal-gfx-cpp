#ifndef PIXEL_H
#define PIXEL_H

#include <gfx/core/types/color4.h>
#include <gfx/math/vec2.h>

namespace gfx::core::types
{

struct Pixel
{
    gfx::math::Vec2i position;
    Color4 color;
};

}

#endif // PIXEL_H
