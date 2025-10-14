#ifndef TRIANGLE_2D_H
#define TRIANGLE_2D_H

#include <gfx/math/vec2.h>
#include <cmath>

namespace gfx::geometry
{

class Triangle
{

public:

    Triangle(const gfx::math::Vec2d& v0, const gfx::math::Vec2d& v1, const gfx::math::Vec2d& v2)
        : v0(v0), v1(v1), v2(v2)
    {
        precompute();
    }

    Triangle()
        : v0(gfx::math::Vec2d::zero()), v1(gfx::math::Vec2d::zero()), v2(gfx::math::Vec2d::zero())
    {
        precompute();
    }

    const gfx::math::Vec2d v0;
    const gfx::math::Vec2d v1;
    const gfx::math::Vec2d v2;

    bool point_inside(const gfx::math::Vec2d& point) const
    {
        double s = inv_area_2x * (a * point.x + b * point.y + c);
        double t = inv_area_2x * (d * point.x + e * point.y + f);

        return s >= 0 && t >= 0 && (s + t) <= 1;
    }

private:
    double inv_area_2x;
    double a, b, c, d, e, f;

    void precompute()
    {
        double area_2x = v0.x * (v1.y - v2.y) + v1.x * (v2.y - v0.y) + v2.x * (v0.y - v1.y);

        if (std::abs(area_2x) < 1e-12)
        {
            inv_area_2x = 0.0;
        }
        else
        {
            inv_area_2x = 1.0 / area_2x;
        }

        a = v2.y - v0.y;
        b = v0.x - v2.x;
        c = v0.y * v2.x - v0.x * v2.y;

        d = v0.y - v1.y;
        e = v1.x - v0.x;
        f = v0.x * v1.y - v0.y * v1.x;
    }
};

}

#endif // TRIANGLE_2D_H

