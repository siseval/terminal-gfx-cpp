#ifndef Color4_H
#define Color4_H

#include <cstdint>
#include <functional>

namespace gfx::core::types
{

class Color4
{

public:

    Color4(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}
    Color4(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

    Color4(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b), a(255) {}
    Color4(int r, int g, int b) : r(r), g(g), b(b), a(255) {}

    Color4(double r, double g, double b, double a) : r(static_cast<uint8_t>(r * 255.0)), g(static_cast<uint8_t>(g * 255.0)), b(static_cast<uint8_t>(b * 255.0)), a(static_cast<uint8_t>(a * 255.0)) {}

    Color4() : Color4(0, 0, 0, 0) {}

    Color4(int32_t color) : r(color >> 24 & 0xFF), g(color >> 16 & 0xFF), b(color >> 8 & 0xFF), a(color & 0xFF) {}

    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a = 255;

    bool operator==(const Color4 &other) const { return r == other.r && g == other.g && b == other.b && a == other.a; }
    void operator=(const Color4 &other) { r = other.r; g = other.g; b = other.b; a = other.a; }

    inline float r_float() const { return r / 255.0f; }
    inline float g_float() const { return g / 255.0f; }
    inline float b_float() const { return b / 255.0f; }
    inline float a_float() const { return a / 255.0f; }

    inline int32_t to_int() const { return (r << 24) | (g << 16) | (b << 8) | (a); }
};



}

template <>
struct std::hash<gfx::core::types::Color4>
{
    size_t operator()(const gfx::core::types::Color4& color) const
    {
        return std::hash<uint8_t>()(color.r ^ (std::hash<uint8_t>()(color.g) << 1)) ^ (std::hash<uint8_t>()(color.b) << 2);
    }
};


#endif // Color4_H
