#ifndef OBB2_H
#define OBB2_H

#include <gfx/math/vec2.h>

namespace gfx::math
{

class OBB2D
{

public:

    Vec2d origin;
    Vec2d side_x;
    Vec2d side_y;

};

}

#endif // OBB2_H
