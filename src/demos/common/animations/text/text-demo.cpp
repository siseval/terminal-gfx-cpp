#include <stack>
#include <gfx/text/font-manager-ttf.h>
#include <demos/common/animations/text/text-demo.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::text
{

using namespace gfx::math;
using namespace demos::common::core;

static std::vector<Vec2d> flatten_bezier(const Vec2d p0, const Vec2d p1, const Vec2d p2, double tolerance = 0.5)
{
    struct BezierSegment
    {
        double t0;
        double t1;
        Vec2d p0;
        Vec2d p1;
    };

    auto bezier_eval { [](const Vec2d &p0, const Vec2d &p1, const Vec2d &p2, const double t) {
        double u = 1.0 - t;
        return Vec2d {
            u * u * p0.x + 2 * u * t * p1.x + t * t * p2.x,
            u * u * p0.y + 2 * u * t * p1.y + t * t * p2.y
        };
    } };

    std::vector<Vec2d> points;
    std::stack<BezierSegment> segments;

    Vec2d start { bezier_eval(p0, p1, p2, 0.0) };
    Vec2d end { bezier_eval(p0, p1, p2, 1.0) };

    segments.push({ 0.0, 1.0, start, end });

    while (!segments.empty())
    {
        BezierSegment segment { segments.top() };
        segments.pop();

        double mid_t { (segment.t0 + segment.t1) / 2.0 };
        Vec2d mid_point { bezier_eval(p0, p1, p2, mid_t) };

        Vec2d line_mid { (segment.p0 + segment.p1) / 2.0 };
        double distance { (mid_point - line_mid).length() };

        if (distance > tolerance)
        {
            segments.push({ mid_t, segment.t1, mid_point, segment.p1 });
            segments.push({ segment.t0, mid_t, segment.p0, mid_point });
        }
        else
        {
            if (points.empty() || points.back() != segment.p0)
            {
                points.push_back(segment.p0);
            }
            points.push_back(segment.p1);
        }
    }

    points.push_back(end);
    return points;
}

static std::vector<Vec2d> flatten_contour(const std::vector<gfx::text::Point> &points)
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
    renderer->clear_items();

    auto font_manager = renderer->get_font_manager();
    auto font = font_manager->load_from_file("/Users/sigurdsevaldrud/documents/code/c++/gfx/assets/fonts/comic-sans.ttf");

    if (!font)
    {
        throw std::runtime_error("Failed to load font.");
    }


    std::shared_ptr<gfx::text::GlyphTTF> glyph;
    // for (auto g : font->get_glyphs())
    // {
    //     if (!g.second->contours.empty())
    //     {
    //         glyph = g.second;
    //         break;
    //     }
    // }
    std::string text { "hallo" };
    for (int i = 0; i < text.length(); i++)
    {
        glyph = font->get_glyph(text[i]);
        for (auto contour : glyph->contours)
        {
            std::vector<Vec2d> points;
            for (auto point : flatten_contour(contour))
            {
                points.push_back({ point.x, point.y });
                num_points++;
            }
            Vec2d center { renderer->center() };

            double kerning { 15.0 };
            Vec2d offset { -(text.length() * kerning / 2) + i * kerning, 0 };
            auto polyline = renderer->create_polyline(center + offset, points, { 255, 255, 255 }, 75.0);
            polyline->set_rotation_degrees(180);
            // polyline->set_anchor({ 0.5, 0.5 });
            polyline->set_scale({ -0.015, 0.015 });
            // polyline->set_close(true);
            // polyline->set_fill(true);
            renderer->add_item(polyline);
        }
    }
}

void TextDemo::render_frame(const double dt)
{
    double t0 { utils::time_us() };
    double time_ms { t0 / 1000.0 };

    renderer->draw_frame();

    last_frame_us = utils::time_us() - t0;
}

void TextDemo::handle_input(const char input)
{
}

void TextDemo::end()
{
    renderer->clear_items();
}

}
