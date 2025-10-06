#include <gfx/fonts/font-manager-ttf.h>
#include <demos/common/animations/text/text-demo.h>

namespace demos::common::animations::text
{

using namespace gfx::math;

static std::vector<Vec2d> flatten_bezier(const Vec2d p0, const Vec2d p1, const Vec2d p2, double tolerance = 0.5)
{
    std::vector<Vec2d> points;

    double dt { 0.1 };

    Vec2d prev_point { p0 };
    points.push_back(prev_point);

    for (double t = dt; t <= 1.0 + 1e-6; t += dt)
    {
        double tt { t * t };
        double u { 1.0 - t };

        Vec2d point {
            u * u * p0.x + 2 * u * t * p1.x + tt * p2.x,
            u * u * p0.y + 2 * u * t * p1.y + tt * p2.y
        };

        double mid_t { t - dt / 2.0 };
        double mid_u { 1 - mid_t };
        Vec2d mid_point {
            mid_u * mid_u * p0.x + 2 * mid_u * mid_t * p1.x + mid_t * mid_t * p2.x,
            mid_u * mid_u * p0.y + 2 * mid_u * mid_t * p1.y + mid_t * mid_t * p2.y
        };

        Vec2d line_mid_point { (prev_point + point) / 2.0 };
        double error { (mid_point - line_mid_point).length() };

        if (error > tolerance)
        {
            dt /= 2.0;
            dt = std::max(dt, 1e-5);
            t -= dt;
            continue;
        }
        else if (error < tolerance / 4.0)
        {
            dt = std::min(dt * 2.0, 0.1);
        }

        points.push_back(point);
        prev_point = point;
    }
    return points;
}

static std::vector<Vec2d> flatten_contour(const std::vector<gfx::fonts::Point> &points)
{
    std::vector<Vec2d> flattened_points;

    int start_index;
    for (int i = 0; i < points.size(); ++i)
    {
        if (points[i].on_curve)
        {
            start_index = i;
            break;
        }
    }

    Vec2d prev_on_point { points[start_index].x, points[start_index].y };
    flattened_points.push_back(prev_on_point);

    int num_points { static_cast<int>(points.size()) };

    for (int i = 1; i <= num_points; ++i)
    {
        const auto &curr_point { points[(start_index + i) % num_points] };

        if (curr_point.on_curve)
        {
            Vec2d curr_on_point { curr_point.x, curr_point.y };
            flattened_points.push_back(curr_on_point);
            prev_on_point = curr_on_point;
        }
        else
        {
            const auto &next_point { points[(start_index + i + 1) % num_points] };
            if (next_point.on_curve)
            {
                Vec2d next_on_point { next_point.x, next_point.y };
                auto bezier_points { flatten_bezier(prev_on_point, Vec2d { curr_point.x, curr_point.y }, next_on_point) };
                flattened_points.insert(flattened_points.end(), bezier_points.begin() + 1, bezier_points.end());
                prev_on_point = next_on_point;
                ++i;
            }
            else
            {
                Vec2d mid_point { (Vec2d { curr_point.x, curr_point.y } + Vec2d { next_point.x, next_point.y }) / 2.0 };
                auto bezier_points { flatten_bezier(prev_on_point, Vec2d { curr_point.x, curr_point.y }, mid_point) };
                flattened_points.insert(flattened_points.end(), bezier_points.begin() + 1, bezier_points.end());
                prev_on_point = mid_point;
            }
        }
    }
    return flattened_points;
}

void TextDemo::init()
{
    auto font_manager = renderer->get_font_manager();
    auto font = font_manager->load_from_file("/Users/sigurdsevaldrud/documents/code/c++/gfx/assets/fonts/MINGLIU.ttf");
    // if (!font)
    // {
    //     throw std::runtime_error("Failed to load font.");
    // }
    //
    // std::vector<Vec2d> points;
    //
    // for (auto point : font->get_glyph('A')->contours[0])
    // {
    //     points.push_back({ point.x, point.y });
    // }

    // auto polyline = renderer->create_polyline({ 100, 300 }, points, { 255, 0, 0 }, 2.0);
    // renderer->add_item(polyline);
}

void TextDemo::render_frame(const double dt)
{
    renderer->draw_frame();
}

void TextDemo::handle_input(const char input)
{
}

void TextDemo::end()
{
    renderer->clear_items();
}

}
