#ifndef BITMAP_2D_H
#define BITMAP_2D_H

#include <gfx/core/render-surface.h>
#include <gfx/core/gfx-primitive-2D.h>
#include <gfx/core/types/color4.h>
#include <gfx/core/types/bitmap.h>
#include <gfx/math/box2.h>
#include <gfx/math/matrix.h>

namespace gfx::primitives
{

class Bitmap2D : public gfx::core::GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx::core::RenderSurface> surface, const gfx::math::Matrix3x3d &transform) const override;
    gfx::math::Box2d get_relative_extent() const override;

    inline void load_bitmap(gfx::core::types::Bitmap bitmap)
    {
        resolution = bitmap.resolution;
        pixels = bitmap.pixels;
    }

    inline gfx::core::types::Color4 get_pixel(const gfx::math::Vec2i pixel) const 
    { 
        if (pixel.x < 0 || pixel.x >= resolution.x || pixel.y < 0 || pixel.y >= resolution.y) 
        {
            return { 0, 0, 0, 0 }; 
        }
        return pixels[pixel.y * resolution.x + pixel.x]; 
    }
    inline void set_pixel(const gfx::math::Vec2i pixel, const gfx::core::types::Color4 color) 
    {
        if (pixel.x < 0 || pixel.x >= resolution.x || pixel.y < 0 || pixel.y >= resolution.y) 
        {
            return; 
        }
        pixels[pixel.y * resolution.x + pixel.x] = color;
    };

    inline void set_resolution(const gfx::math::Vec2d new_resolution) { resolution = new_resolution; pixels.resize(resolution.x * resolution.y); }
    inline gfx::math::Vec2d get_resolution() const { return resolution; }

private:

    gfx::math::Vec2i resolution;
    std::vector<gfx::core::types::Color4> pixels;
};

};

#endif // BITMAP_2D_H
