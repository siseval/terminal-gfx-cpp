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


void rasterize_filled_triangle(const Triangle &triangle, const Color4 color, const std::function<void(const Pixel&)> emit_pixel)
{
    Box2i bounds {
        Vec2d { 
            std::min({triangle.v0.x,triangle.v1.x,triangle.v2.x }), 
            std::min({triangle.v0.y,triangle.v1.y,triangle.v2.y }) 
        }.round(),
        Vec2d { 
            std::max({triangle.v0.x,triangle.v1.x,triangle.v2.x }), 
            std::max({triangle.v0.y,triangle.v1.y,triangle.v2.y }) 
        }.round()
    };

    double a = triangle.get_a();
    double b = triangle.get_b();
    double c = triangle.get_c();

    double d = triangle.get_d();
    double e = triangle.get_e();
    double f = triangle.get_f();

    double g = triangle.get_g();
    double h = triangle.get_h();
    double i = triangle.get_i();

    double area = triangle.get_area();

    if (area == 0.0)
    {
        return;
    }

    double w0_row = a * (bounds.min.x + 0.5) + b * (bounds.min.y + 0.5) + c;
    double w1_row = d * (bounds.min.x + 0.5) + e * (bounds.min.y + 0.5) + f;
    double w2_row = g * (bounds.min.x + 0.5) + h * (bounds.min.y + 0.5) + i;

    for (int y = bounds.min.y; y <= bounds.max.y; ++y)
    {
        double w0 = w0_row;
        double w1 = w1_row;
        double w2 = w2_row;

        for (int x = bounds.min.x; x <= bounds.max.x; ++x)
        {
            if ((w0 * w1 >= 0) && (w1 * w2 >= 0)) 
            {
                emit_pixel(Pixel { Vec2i { x, y }, color });
            }

            w0 += a;
            w1 += d;
            w2 += g;
        }

        w0_row += b;
        w1_row += e;
        w2_row += h;
    }
}

}
