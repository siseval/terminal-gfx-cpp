#include <gfx/primitives/polyline-2D.h>

namespace gfx::primitives
{

using namespace gfx::core;
using namespace gfx::math;


Box2d Polyline2D::get_relative_extent() const
{
    Vec2d min = Vec2d::zero();
    Vec2d max = Vec2d::zero();

    for (auto point : points)
    {
        if (point.x < min.x)
        {
            min.x = point.x;
        }
        if (point.x > max.x)
        {
            max.x = point.x;
        }
        if (point.y < min.y)
        {
            min.y = point.y;
        }
        if (point.y > max.y)
        {
            max.y = point.y;
        }
    }

    return { min, max };
}

void Polyline2D::rasterize_fill(std::shared_ptr<GfxContext2D> context) const
{
    std::vector<Vec2d> transformed_points;
    for (auto point : points)
    {
        transformed_points.push_back(utils::apply_transform(point, context->get_transform() * get_transform()));
    }

    std::vector<Box2d> edges;

    for (int i = 0; i < points.size() - 1; i++)
    {
        edges.push_back({ transformed_points[i], transformed_points[i + 1] });
    }
    edges.push_back({ transformed_points.back(), transformed_points.front() });

    Box2d bounds = get_global_bounds(context);
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
            if (inside && should_fill_pixel(context, pixel))
            {
                context->write_pixel(Vec2i { x, y }, get_color());
            }
        }
    }
}

void Polyline2D::rasterize(std::shared_ptr<GfxContext2D> context) const
{
    if (points.size() < 2)
    {
        return;
    }
    Matrix3x3d full_transform = context->get_transform() * get_transform();

    std::vector<Vec2d> transformed_points;
    for (auto point : points)
    {
        transformed_points.push_back(utils::apply_transform(point, full_transform));
    }

    for (int i = 0; i < points.size() - 1; i++)
    {
        utils::rasterize_line(context, transformed_points[i], transformed_points[i + 1], get_line_thickness(), get_color());
    }
    if (do_close)
    {
        utils::rasterize_line(context, transformed_points.front(), transformed_points.back(), get_line_thickness(), get_color());
    }

    if (get_fill() > 0)
    {
        rasterize_fill(context);
    }
}


}
