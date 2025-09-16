#include <gfx/utils/rasterize.h>

namespace gfx::utils
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::math;


void rasterize_circle(std::shared_ptr<RenderSurface> surface, const Vec2d center, const double radius, const Color3 color, const Vec2d scale)
{
    Vec2d scaled_radius = Vec2d::create(radius) * scale;

    for (int y = -scaled_radius.y; y <= scaled_radius.y; y++)
    {
        for (int x = -scaled_radius.x; x <= scaled_radius.x; x++)
        {
            if (x * x + y * y <= scaled_radius.x * scaled_radius.y)
            {
                surface->write_pixel(center.round() + Vec2i { x, y }, color);
            }
        }
    }
}

void rasterize_filled_polygon(std::shared_ptr<RenderSurface> surface, const std::vector<Vec2d> vertices, const Color3 color)
{
    if (vertices.size() < 3)
    {
        return;
    }

    std::vector<Box2d> edges;
    for (int i = 0; i < vertices.size() - 1; i++)
    {
        edges.push_back({ vertices[i], vertices[i + 1] });
    }
    edges.push_back({ vertices.back(), vertices.front() });

    Box2d bounds = Box2d { vertices[0], vertices[0] };
    bounds.expand(vertices);

    Box2i rounded_bounds = { bounds.min.round(), bounds.max.round() };
    for (int y = rounded_bounds.min.y; y < rounded_bounds.max.y; y++)
    {
        for (int x = rounded_bounds.min.x; x < rounded_bounds.max.x; x++)
        {
            Vec2d pixel = Vec2d { static_cast<double>(x), static_cast<double>(y) };
            bool inside = false;
            for (auto edge : edges)
            {
                bool intersects_y = (edge.min.y > pixel.y) != (edge.max.y > pixel.y);
                if (!intersects_y)
                {
                    continue;
                }
                double progress = (pixel.y - edge.min.y) / (edge.max.y - edge.min.y);
                bool intersects = pixel.x < (edge.max.x - edge.min.x) * progress + edge.min.x;
                if (intersects)
                {
                    inside = !inside;
                }
            }
            if (inside)
            {
                surface->write_pixel(Vec2i { x, y }, color);
            }
        }
    }
}

void rasterize_filled_triangle(std::shared_ptr<RenderSurface> surface, const Vec2d v0, const Vec2d v1, const Vec2d v2, const Color3 color)
{
    Box2d bounds;
    bounds.min = Vec2d { std::min({ v0.x, v1.x, v2.x }), std::min({ v0.y, v1.y, v2.y }) };
    bounds.max = Vec2d { std::max({ v0.x, v1.x, v2.x }), std::max({ v0.y, v1.y, v2.y }) };

    for (int y = bounds.min.y; y <= bounds.max.y; y++)
    {
        for (int x = bounds.min.x; x <= bounds.max.x; x++)
        {
            Vec2d pos = Vec2d { static_cast<double>(x), static_cast<double>(y) };

            double area = 0.5 * (-v1.y * v2.x + v0.y * (-v1.x + v2.x) + v0.x * (v1.y - v2.y) + v1.x * v2.y);
            double s = 1 / (2 * area) * (v0.y * v2.x - v0.x * v2.y + (v2.y - v0.y) * pos.x + (v0.x - v2.x) * pos.y);
            double t = 1 / (2 * area) * (v0.x * v1.y - v0.y * v1.x + (v0.y - v1.y) * pos.x + (v1.x - v0.x) * pos.y);

            if (s >= 0 && t >= 0 && (s + t) <= 1)
            {
                surface->write_pixel(pos.round(), color);
            }
        }
    }
}

void rasterize_line(std::shared_ptr<RenderSurface> surface, const Vec2d start, const Vec2d end, const double line_thickness, const Color3 color)
{
    double line_extent = line_thickness / 2.0;
    Vec2d normal = (end - start).normal().normalize();

    Vec2d v0 = start + normal * line_extent;
    Vec2d v1 = start - normal * line_extent;
    Vec2d v2 = end + normal * line_extent;
    Vec2d v3 = end - normal * line_extent;

    rasterize_filled_triangle(surface, v0, v1, v2, color);
    rasterize_filled_triangle(surface, v1, v3, v2, color);
}

void rasterize_box_corners(std::shared_ptr<RenderSurface> surface, const Box2d bounds, const Color3 color)
{
    Box2i rounded_bounds = { bounds.min.round(), bounds.max.round() };
    surface->write_pixel(rounded_bounds.min, color);
    surface->write_pixel({ rounded_bounds.min.x, rounded_bounds.max.y }, color);
    surface->write_pixel(rounded_bounds.max, color);
    surface->write_pixel({ rounded_bounds.max.x, rounded_bounds.min.y }, color);
}

void rasterize_cross(std::shared_ptr<RenderSurface> surface, const Vec2d pos, const double size, const Color3 color)
{
    int half_size = static_cast<int>(size / 2);
    for (int i = -half_size; i <= half_size; i++)
    {
        surface->write_pixel(pos.round() + Vec2i { i, 0 }, color);
        surface->write_pixel(pos.round() + Vec2i { 0, i }, color);
    }
}

}
