#ifndef TRIANGLE_2D_H
#define TRIANGLE_2D_H

#include <gfx/math/vec2.h>

namespace gfx::math
{

class Triangle
{

public:

    Vec2d v0;
    Vec2d v1;
    Vec2d v2;

    bool point_inside(Vec2d point) const
    {
        double area = 0.5 * (-v1.y * v2.x + v0.y * (-v1.x + v2.x) + v0.x * (v1.y - v2.y) + v1.x * v2.y);
        double s = 1 / (2 * area) * (v0.y * v2.x - v0.x * v2.y + (v2.y - v0.y) * point.x + (v0.x - v2.x) * point.y);
        double t = 1 / (2 * area) * (v0.x * v1.y - v0.y * v1.x + (v0.y - v1.y) * point.x + (v1.x - v0.x) * point.y);

        return s >= 0 && t >= 0 && (s + t) <= 1;
    }
};

}

#endif // TRIANGLE_2D_H
