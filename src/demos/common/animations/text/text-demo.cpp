#include <gfx/text/font-manager-ttf.h>
#include <gfx/geometry/flatten.h>
#include <demos/common/animations/text/text-demo.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::text
{

using namespace gfx::math;
using namespace demos::common::core;



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
            std::vector<std::pair<Vec2d, bool>> cont;
            for (auto point : contour)
            {
                cont.push_back({ { point.x, point.y }, point.on_curve });
            }
            std::vector<Vec2d> points;
            for (auto point : gfx::geometry::flatten_contour(cont))
            {
                Vec2d flattened { point };
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

void TextDemo::handle_input(const int input)
{
}

void TextDemo::end()
{
    renderer->clear_items();
}

}
