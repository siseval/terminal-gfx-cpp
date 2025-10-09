#ifndef UNITS_H
#define UNITS_H

#include <gfx/math/vec2.h>

namespace demos::common::animations::space::units
{

using namespace gfx::math;

static constexpr double G = 4 * std::numbers::pi * std::numbers::pi;

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

inline double pixels_to_metres(const double pixels, const double view_metres, const double resolution_pixels)
{
    return (pixels / resolution_pixels) * view_metres;
}

inline Vec2d pixels_to_metres(const Vec2d pixels, const Vec2d view_metres, const Vec2d resolution_pixels)
{
    return Vec2d {
        pixels_to_metres(pixels.x, view_metres.x, resolution_pixels.x),
        pixels_to_metres(pixels.y, view_metres.y, resolution_pixels.y)
    };
}

}

#endif // UNITS_H
