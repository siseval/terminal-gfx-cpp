#ifndef CURSPP_GRAPHICS_H
#define CURSPP_GRAPHICS_H

#include <ncurses.h>
#include <gfx/core/types/color3.h>
#include <gfx/core/draw/pixel-tree.h>
#include <gfx/utils/transform.h>
#include <gfx/math/vec2.h>
#include <gfx/math/matrix.h>
#include <gfx/math/box2.h>

namespace gfx::core
{

constexpr uint8_t GFX_DEDICATED_COLOR_START_INDEX = 128;
const types::Color3 GFX_BOUNDS_COLOR = { 255, 255, 255 };
const types::Color3 GFX_ANCHOR_COLOR = { 255, 255, 255 };

class GfxContext2D
{

public:

    GfxContext2D(const gfx::math::Vec2i resolution, const gfx::math::Vec2i origin = { 0, 0 }, const gfx::math::Vec2d viewport_scaling = gfx::math::Vec2d { 2, 1 })
        : resolution(resolution), origin(origin), viewport_scaling(viewport_scaling) 
    {
        palette = std::make_unique<std::unordered_map<types::Color3, uint8_t, std::hash<types::Color3>>>(),
        frame_buffer = std::make_unique<std::vector<int32_t>>(
            static_cast<size_t>(resolution.x * viewport_scaling.x) * 
            static_cast<size_t>(resolution.y * viewport_scaling.y) / 2, 0);
    }
    
    gfx::math::Matrix3x3d get_transform();

    inline gfx::math::Vec2d scale_with_viewport(const gfx::math::Vec2d vec) { return vec * viewport_scaling; }

    uint8_t add_color(const types::Color3 color);
    void set_color(const types::Color3 color);

    inline gfx::math::Vec2i get_resolution() const { return resolution; }
    inline gfx::math::Vec2i get_origin() const { return origin; }
    inline gfx::math::Vec2d get_viewport_scaling() const { return viewport_scaling; }
    inline void set_viewport_scaling(const gfx::math::Vec2d scaling) { viewport_scaling = scaling; }

    void write_pixel(const gfx::math::Vec2i pos, const types::Color3 color);
    void erase_pixel(const gfx::math::Vec2i pos);

    void clear_frame_buffer();

    void draw_frame_buffer();


private:

    gfx::math::Vec2i resolution;
    gfx::math::Vec2i origin;
    gfx::math::Vec2d viewport_scaling;
    int color_index = 0;
    std::unique_ptr<std::unordered_map<types::Color3, uint8_t, std::hash<types::Color3>>> palette;
    std::unique_ptr<std::vector<int32_t>> frame_buffer;
};


}

#endif // CURSPP_GRAPHICS_H
