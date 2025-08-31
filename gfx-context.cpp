#include "gfx-context.h"

namespace curspp::graphics
{

std::shared_ptr<gfx_context> create_context(const coord2D resolution, const coord2D origin, const coord2D viewport_scaling)
{
    return std::make_shared<gfx_context>(gfx_context {
        resolution,
        origin,
        viewport_scaling,
        std::make_unique<std::unordered_map<Color3, uint8_t, std::hash<Color3>>>(),
        std::make_unique<std::vector<uint8_t>>(static_cast<size_t>(resolution.x) * static_cast<size_t>(resolution.y) / 2, 0)
    });
}

void add_color(std::shared_ptr<gfx_context> context, const Color3 color)
{
    if (context->palette->size() >= 255)
    {
        return;
    }
    uint8_t color_index = context->palette->size() + 1;
    context->palette->insert({ color, static_cast<uint8_t>(color_index) });
    init_color(color_index,
               static_cast<int16_t>(color.r * 4),
               static_cast<int16_t>(color.g * 4),
               static_cast<int16_t>(color.b * 4));
}

void write_pixel(std::shared_ptr<gfx_context> context, const coord2D pos, const Color3 color)
{
    if (pos.x < 0 || pos.x >= context->resolution.x || pos.y < 0 || pos.y >= context->resolution.y)
    {
        return;
    }

    bool left_in_pixel = pos.x % 2 == 0;
    bool top_in_pixel = pos.y % 2 == 0;
    uint16_t frame_buffer_index = (pos.y / 2) * context->resolution.x + pos.x / 2;

    if (left_in_pixel)
    {
        if (top_in_pixel)
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b00001000;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b00000010;
        }
    }
    else
    {
        if (top_in_pixel)
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b00000100;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b00000001;
        }
    }
}

void erase_pixel(std::shared_ptr<gfx_context> context, const coord2D pos)
{
    if (pos.x < 0 || pos.x >= context->resolution.x || pos.y < 0 || pos.y >= context->resolution.y)
    {
        return;
    }

    bool left_in_pixel = pos.x % 2 == 0;
    bool top_in_pixel = pos.y % 2 == 0;
    uint16_t frame_buffer_index = (pos.y / 2) * context->resolution.x + pos.x / 2;

    if (left_in_pixel)
    {
        if (top_in_pixel)
        {
            context->frame_buffer->at(frame_buffer_index) &= 0b11110111;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) &= 0b11111101;
        }
    }
    else
    {
        if (top_in_pixel)
        {
            context->frame_buffer->at(frame_buffer_index) &= 0b11111011;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b11111110;
        }
    }
}

void clear_frame_buffer(std::shared_ptr<gfx_context> context)
{
    for (uint8_t &pixel : *context->frame_buffer)
    {
        pixel = 0;
    }
}

void draw_frame_buffer(std::shared_ptr<gfx_context> context)
{
    coord2D frame_buffer_dimensions = context->resolution / 2;
    for (coord_type y = 0; y < frame_buffer_dimensions.y; y++)
    {
        for (coord_type x = 0; x < frame_buffer_dimensions.x / 2; x++)
        {
            uint16_t frame_buffer_index = y * context->resolution.x + x;
            uint8_t pixel_value = context->frame_buffer->at(frame_buffer_index);

            std::string pixel = pixel_tree[(pixel_value & 0b00001000) >> 3]
                                           [(pixel_value & 0b00000100) >> 2]
                                           [(pixel_value & 0b00000010) >> 1]
                                           [(pixel_value & 0b00000001)];

            add_str(context->origin + coord2D { x, y }, pixel);
        }
    }
}


}
