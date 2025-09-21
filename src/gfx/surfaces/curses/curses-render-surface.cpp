#include <gfx/surfaces/curses-render-surface.h>

namespace gfx::surfaces
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;


void CursesRenderSurface::present()
{
    Vec2i frame_buffer_dimensions = resolution / 2;
    for (int y = 0; y < frame_buffer_dimensions.y; y++)
    {
        for (int x = 0; x < frame_buffer_dimensions.x; x++)
        {
            int frame_buffer_index = y * resolution.x + x;
            int64_t pixel_value = frame_buffer->at(frame_buffer_index);

            std::string pixel = pixel_tree[(pixel_value & 0b1000) >> 3]
                                           [(pixel_value & 0b0100) >> 2]
                                           [(pixel_value & 0b0010) >> 1]
                                           [(pixel_value & 0b0001)];

            Color4 color = Color4(pixel_value >> 32);
            set_color(color);
            mvaddstr(y, x, pixel.data());
        }
    }
}

void CursesRenderSurface::clear() const
{
    erase();
}

void CursesRenderSurface::clear_frame_buffer()
{
    for (int64_t &pixel : *frame_buffer)
    {
        pixel = 0;
    }
}

void CursesRenderSurface::write_pixel(const gfx::math::Vec2i pos, const gfx::core::types::Color4 color)
{
    if (pos.x < 0 || pos.x >= resolution.x || pos.y < 0 || pos.y >= resolution.y)
    {
        return;
    }

    bool left_in_pixel = pos.x % 2 == 0;
    bool top_in_pixel = pos.y % 2 == 0;
    int frame_buffer_index = (pos.y / 2) * resolution.x + pos.x / 2;

    int64_t color_mask = static_cast<int64_t>(color.to_int()) << 32;
    frame_buffer->at(frame_buffer_index) &= 0x00000000000000FF;
    frame_buffer->at(frame_buffer_index) |= color_mask;

    int8_t bit_masks[2][2] = {
        { 0b0001, 0b0010 },
        { 0b0100, 0b1000 }
    };

    frame_buffer->at(frame_buffer_index) |= 
        bit_masks[top_in_pixel][left_in_pixel];
}

void CursesRenderSurface::set_color(const Color4 color)
{
    auto iterator = palette->find(color);
    uint8_t index = 0;

    if (iterator != palette->end())
    {
        index = iterator->second;
    }
    else
    {
        index = add_color(color);
    }
    attron(COLOR_PAIR(index));
}

uint8_t CursesRenderSurface::add_color(const Color4 color)
{
    if (color_index + DEDICATED_CURSES_COLOR_START_INDEX >= 255)
    {
        color_index = 0;
    }
    uint8_t index = color_index + DEDICATED_CURSES_COLOR_START_INDEX;
    palette->insert(std::pair(color, index));
    color_index += 1;
    init_color(index, color.r_float() * 1000, color.g_float() * 1000, color.b_float() * 1000);
    init_pair(index, index, -1);
    return index;
}

}
