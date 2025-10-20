#ifndef OBB_2D_H
#define OBB_2D_H

#include <gfx/math/vec2.h>

namespace gfx::core::types
{

struct OBB2D
{

    gfx::math::Vec2d origin;
    gfx::math::Vec2d side_x;
    gfx::math::Vec2d side_y;

};

}

#endif // OBB_2D_H
