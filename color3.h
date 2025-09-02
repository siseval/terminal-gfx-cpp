#ifndef COLOR3_H
#define COLOR3_H

#include <cstdint>
#include <functional>

namespace curspp::graphics
{

class Color3
{

public:

    Color3(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    Color3() : Color3(0, 0, 0) {}

    Color3(int32_t color) : r(color >> 16 & 0xFF), g(color >> 8 & 0xFF), b(color & 0xFF) {}

    uint8_t r;
    uint8_t g;
    uint8_t b;

    bool operator==(const Color3 &other) const { return r == other.r && g == other.g && b == other.b; }
    void operator=(const Color3 &other) { r = other.r; g = other.g; b = other.b; }

    inline float r_float() const { return r / 255.0f; }
    inline float g_float() const { return g / 255.0f; }
    inline float b_float() const { return b / 255.0f; }

    inline int32_t to_int() const { return (r << 16) | (g << 8) | b; }
};



}

template <>
struct std::hash<curspp::graphics::Color3>
{
    size_t operator()(const curspp::graphics::Color3& color) const
    {
        return std::hash<uint8_t>()(color.r ^ (std::hash<uint8_t>()(color.g) << 1)) ^ (std::hash<uint8_t>()(color.b) << 2);
    }
};


#endif // COLOR3_H
