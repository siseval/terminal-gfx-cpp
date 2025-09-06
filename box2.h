#ifndef BOX2D_H
#define BOX2D_H

#include "vec2.h"

namespace curspp
{

template <typename T>
class Box2
{

public:

    Vec2<T> min;
    Vec2<T> max;

    inline Vec2<T> size() const
    {
        return max - min;
    }

};

using Box2d = Box2<double>;
using Box2i = Box2<int32_t>;

}

#endif // BOX2D_H


