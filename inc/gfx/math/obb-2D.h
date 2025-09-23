#ifndef OBB_2D_H
#define OBB_2D_H

#include <gfx/math/vec2.h>

namespace gfx::math
{

struct OBB2D
{

    Vec2d origin;
    Vec2d side_x;
    Vec2d side_y;

};

}

#endif // OBB_2D_H
