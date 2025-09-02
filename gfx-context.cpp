#include "gfx-context.h"

namespace curspp::graphics
{

std::shared_ptr<gfx_context> create_context(const coord2D resolution, const coord2D origin, const coord2D viewport_scaling)
{
    return std::make_shared<gfx_context>(gfx_context {
        resolution * viewport_scaling,
        origin,
        viewport_scaling,
        std::make_unique<std::unordered_map<Color3, uint8_t, std::hash<Color3>>>(),
        std::make_unique<std::vector<uint32_t>>(static_cast<size_t>(resolution.x * viewport_scaling.x) * static_cast<size_t>(resolution.y * viewport_scaling.y) / 2, 0)
    });
}

uint8_t add_color(std::shared_ptr<gfx_context> context, const Color3 color)
{
    if (context->palette->size() + GFX_DEDICATED_COLOR_START_INDEX >= 255)
    {
        return -1;
    }
    uint8_t color_index = context->palette->size() + GFX_DEDICATED_COLOR_START_INDEX;
    context->palette->insert(std::pair(color, color_index));
    init_color(color_index, color.r_float() * 1000, color.g_float() * 1000, color.b_float() * 1000);
    init_pair(color_index, color_index, -1);
    return color_index;
}

void set_color(std::shared_ptr<gfx_context> context, const Color3 color)
{
    auto iterator = context->palette->find(color);
    uint8_t color_index = -1;

    if (iterator != context->palette->end())
    {
        color_index = iterator->second;
    }
    else
    {
        color_index = add_color(context, color);
    }
    attron(COLOR_PAIR(color_index));
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

    int32_t color_int = (color.to_int() << 8);
    context->frame_buffer->at(frame_buffer_index) |= color_int;
    if (left_in_pixel)
    {
        if (top_in_pixel)
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b1000;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b0010;
        }
    }
    else
    {
        if (top_in_pixel)
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b0100;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) |= 0b0001;
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
            context->frame_buffer->at(frame_buffer_index) &= 0b0111;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) &= 0b1101;
        }
    }
    else
    {
        if (top_in_pixel)
        {
            context->frame_buffer->at(frame_buffer_index) &= 0b1011;
        }
        else
        {
            context->frame_buffer->at(frame_buffer_index) &= 0b1110;
        }
    }
}

void clear_frame_buffer(std::shared_ptr<gfx_context> context)
{
    for (uint32_t &pixel : *context->frame_buffer)
    {
        pixel &= 0x1110;
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
            uint32_t pixel_value = context->frame_buffer->at(frame_buffer_index);

            std::string pixel = pixel_tree[(pixel_value & 0b1000) >> 3]
                                           [(pixel_value & 0b0100) >> 2]
                                           [(pixel_value & 0b0010) >> 1]
                                           [(pixel_value & 0b0001)];


            Color3 color = Color3(pixel_value >> 8);
            set_color(context, color);
            add_str(context->origin + coord2D { x, y }, pixel);
        }
    }
}


}
