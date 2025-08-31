#ifndef CURSPP_GRAPHICS_H
#define CURSPP_GRAPHICS_H

#include "curspp.h"
#include "color3.h"
#include "pixel-tree.h"

namespace curspp::graphics
{

struct gfx_context
{
    coord2D resolution;
    coord2D origin;
    coord2D viewport_scaling;
    std::unique_ptr<std::unordered_map<Color3, uint8_t, std::hash<Color3>>> palette;
    std::unique_ptr<std::vector<uint8_t>> frame_buffer;
};

std::shared_ptr<gfx_context> create_context(const coord2D resolution, const coord2D origin = coord2D { 0, 0 }, const coord2D viewport_scaling = coord2D { 2, 1 });

inline coord2D scale_with_viewport(std::shared_ptr<gfx_context> context, coord2D vec) { return vec * context->viewport_scaling; }

void add_color(std::shared_ptr<gfx_context> context, const Color3 color);

void write_pixel(std::shared_ptr<gfx_context> context, const coord2D pos, const Color3 color);
void erase_pixel(std::shared_ptr<gfx_context> context, const coord2D pos);

void clear_frame_buffer(std::shared_ptr<gfx_context> context);

void draw_frame_buffer(std::shared_ptr<gfx_context> context);

}

#endif // CURSPP_GRAPHICS_H
