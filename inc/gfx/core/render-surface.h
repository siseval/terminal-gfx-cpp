#ifndef RENDER_SURFACE_H
#define RENDER_SURFACE_H

#include <gfx/core/types/color3.h>
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
    virtual void write_pixel(const gfx::math::Vec2i pos, const types::Color3 color) = 0;

    inline gfx::math::Vec2i get_resolution() const { return resolution; }

protected:

    gfx::math::Vec2i resolution;
};

}

#endif // RENDER_SURFACE_H
