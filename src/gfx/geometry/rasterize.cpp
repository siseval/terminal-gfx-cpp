#include <gfx/core/render-surface.h>
#include <gfx/math/vec2.h>
#include <gfx/math/box2.h>
#include <gfx/math/matrix.h>
#include <gfx/geometry/rasterize.h>
#include <gfx/geometry/triangulate.h>
#include <gfx/utils/transform.h>

namespace gfx::geometry
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;


void rasterize_filled_triangle(std::shared_ptr<RenderSurface> surface, const Triangle &triangle, const Color4 color, const int depth)
{
    Box2d bounds {
        { 
            std::min({triangle.v0.x,triangle.v1.x,triangle.v2.x }), 
            std::min({triangle.v0.y,triangle.v1.y,triangle.v2.y }) 
        },
        { 
            std::max({triangle.v0.x,triangle.v1.x,triangle.v2.x }), 
            std::max({triangle.v0.y,triangle.v1.y,triangle.v2.y }) 
        }
    };

    for (int y = bounds.min.y; y <= bounds.max.y; y++)
    {
        for (int x = bounds.min.x; x <= bounds.max.x; x++)
        {
            Vec2d pos { static_cast<double>(x), static_cast<double>(y) };

            if (triangle.point_inside(pos))
            {
                surface->write_pixel(pos.round(), color, depth);
            }
        }
    }
}

}
