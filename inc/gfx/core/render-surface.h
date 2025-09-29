#ifndef RENDER_SURFACE_H
#define RENDER_SURFACE_H

#include <gfx/core/types/color4.h>
#include <gfx/math/vec2.h>

namespace gfx::core
{

class RenderSurface 
{

public:

    RenderSurface(const gfx::math::Vec2i resolution)
        : resolution(resolution) {}

    virtual void present() = 0;
    virtual void clear() const = 0;

    virtual void clear_frame_buffer() = 0;
    virtual void clear_palette() = 0;

    virtual void write_pixel(const gfx::math::Vec2i pos, const types::Color4 color) = 0;
    inline void write_pixels(const std::vector<gfx::math::Vec2i> &positions, const types::Color4 color)
    {
        for (auto pos : positions)
        {
            write_pixel(pos, color);
        }
    }

    inline void set_resolution(const gfx::math::Vec2i new_resolution) { resolution = new_resolution; }
    inline gfx::math::Vec2i get_resolution() const { return resolution; }

protected:

    gfx::math::Vec2i resolution;
};

}

#endif // RENDER_SURFACE_H
