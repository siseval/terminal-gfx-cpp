#ifndef UNITS_H
#define UNITS_H

#include <gfx/math/vec2.h>

namespace demos::common::animations::space::units
{

using namespace gfx::math;

static constexpr double G = 6.67430e-11;
static constexpr double AU = 1.496e11;

inline double metres_to_pixels(const double metres, const double view_metres, const double resolution_pixels)
{
    return (metres / view_metres) * resolution_pixels;
}

inline Vec2d metres_to_pixels(const Vec2d metres, const Vec2d view_metres, const Vec2d resolution_pixels)
{
    return Vec2d {
        metres_to_pixels(metres.x, view_metres.x, resolution_pixels.x),
        metres_to_pixels(metres.y, view_metres.y, resolution_pixels.y)
    };
}

}

#endif // UNITS_H
