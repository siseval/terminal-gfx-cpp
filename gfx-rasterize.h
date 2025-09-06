#ifndef GFX_RASTERIZE_H
#define GFX_RASTERIZE_H

#include "gfx-context.h"
#include "box2.h"

namespace curspp::graphics
{

void rasterize_circle(std::shared_ptr<gfx_context> context, const Vec2d center, const double radius, const Color3 color);
void rasterize_line(std::shared_ptr<gfx_context> context, const Vec2d start, const Vec2d end, double line_thickness, const Color3 color);
void rasterize_box_corners(std::shared_ptr<gfx_context> context, const BBox2D bounds);
void rasterize_point(std::shared_ptr<gfx_context> context, const Vec2d pos);

}

#endif // GFX_RASTERIZE_H
