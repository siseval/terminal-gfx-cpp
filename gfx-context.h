#ifndef CURSPP_GRAPHICS_H
#define CURSPP_GRAPHICS_H

#include "curspp.h"
#include "color3.h"
#include "matrix.h"
#include "box2.h"
#include "pixel-tree.h"

namespace curspp::graphics
{

constexpr uint8_t GFX_DEDICATED_COLOR_START_INDEX = 200;
const Color3 GFX_BOUNDS_COLOR = { 255, 255, 255 };
const Color3 GFX_ANCHOR_COLOR = { 255, 255, 255 };

using BBox2D = Box2<double>;

struct gfx_context
{
    Vec2i resolution;
    Vec2i origin;
    Vec2d viewport_scaling;
    std::unique_ptr<std::unordered_map<Color3, uint8_t, std::hash<Color3>>> palette;
    std::unique_ptr<std::vector<int32_t>> frame_buffer;
};

std::shared_ptr<gfx_context> create_context(const Vec2i resolution, const Vec2i origin = { 0, 0 }, const Vec2d viewport_scaling = Vec2d { 2, 1 });
Matrix3x3d get_global_transform(std::shared_ptr<gfx_context> context);

inline Vec2d scale_with_viewport(std::shared_ptr<gfx_context> context, const Vec2d vec) { return vec * context->viewport_scaling; }

uint8_t add_color(std::shared_ptr<gfx_context> context, const Color3 color);
void set_color(std::shared_ptr<gfx_context> context, const Color3 color);

void write_pixel(std::shared_ptr<gfx_context> context, const Vec2i pos, const Color3 color);
void erase_pixel(std::shared_ptr<gfx_context> context, const Vec2i pos);

void clear_frame_buffer(std::shared_ptr<gfx_context> context);

void draw_frame_buffer(std::shared_ptr<gfx_context> context);

}

#endif // CURSPP_GRAPHICS_H
