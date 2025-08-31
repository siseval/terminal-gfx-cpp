#ifndef COLOR3_H
#define COLOR3_H

#include <cstdint>
#include <functional>

namespace curspp::graphics
{

class Color3
{

public:

    uint8_t r;
    uint8_t g;
    uint8_t b;

    bool operator==(const Color3 &other) const { return r == other.r && g == other.g && b == other.b; }
    void operator=(const Color3 &other) { r = other.r; g = other.g; b = other.b; }

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
