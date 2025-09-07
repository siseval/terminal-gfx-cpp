#ifndef CURSPP_GRAPHICS_H
#define CURSPP_GRAPHICS_H

#include "curspp.h"
#include "color3.h"
#include "matrix.h"
#include "box2.h"
#include "pixel-tree.h"
#include "gfx-utils-transform.h"

namespace curspp::gfx
{

constexpr uint8_t GFX_DEDICATED_COLOR_START_INDEX = 128;
const Color3 GFX_BOUNDS_COLOR = { 255, 255, 255 };
const Color3 GFX_ANCHOR_COLOR = { 255, 255, 255 };

class GfxContext2D
{

public:

    GfxContext2D(const Vec2i resolution, const Vec2i origin = { 0, 0 }, const Vec2d viewport_scaling = Vec2d { 2, 1 })
        : resolution(resolution), origin(origin), viewport_scaling(viewport_scaling) 
    {
        palette = std::make_unique<std::unordered_map<Color3, uint8_t, std::hash<Color3>>>(),
        frame_buffer = std::make_unique<std::vector<int32_t>>(
            static_cast<size_t>(resolution.x * viewport_scaling.x) * 
            static_cast<size_t>(resolution.y * viewport_scaling.y) / 2, 0);
    }
    
    Matrix3x3d get_transform();

    inline Vec2d scale_with_viewport(const Vec2d vec) { return vec * viewport_scaling; }

    uint8_t add_color(const Color3 color);
    void set_color(const Color3 color);

    inline Vec2i get_resolution() const { return resolution; }
    inline Vec2i get_origin() const { return origin; }
    inline Vec2d get_viewport_scaling() const { return viewport_scaling; }
    inline void set_viewport_scaling(const Vec2d scaling) { viewport_scaling = scaling; }

    void write_pixel(const Vec2i pos, const Color3 color);
    void erase_pixel(const Vec2i pos);

    void clear_frame_buffer();

    void draw_frame_buffer();


private:

    Vec2i resolution;
    Vec2i origin;
    Vec2d viewport_scaling;
    int color_index = 0;
    std::unique_ptr<std::unordered_map<Color3, uint8_t, std::hash<Color3>>> palette;
    std::unique_ptr<std::vector<int32_t>> frame_buffer;
};


}

#endif // CURSPP_GRAPHICS_H
