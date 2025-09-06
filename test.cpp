#include "curspp.h"
#include "gfx-render-2D.h"

using namespace curspp;
using namespace curspp::graphics;

void gfx_test();
void circle_test();

int main()
{
    gfx_test();
}

void gfx_test()
{
    init();
    set_bold(true);
    bool run = true;

    Vec2d screen_size = get_screen_size() * 2;

    GfxRender2D renderer(screen_size);
    renderer.set_viewport_scaling({ 2, 1 });
    Vec2d center = renderer.center();

    Vec2d radius = { center.y / 2, center.y / 2 };
    auto ellipse = renderer.create_ellipse(center, radius, Color3 { 240, 240, 20 }, 3);
    ellipse->set_anchor({ 0.5, 0.5 });
    ellipse->set_draw_anchor(true);
    // ellipse->set_scale({ 2, 1 });
    // ellipse->set_pos({ 0, 0 });//{ 20, 10 });
    renderer.add_item(ellipse);

    std::vector<Vec2d> points = { Vec2d { 0, 0 }, Vec2d { 30, 0 }, Vec2d { 15, 15 } };
    auto polyline = renderer.create_polyline(points, Color3 { 20, 20, 240 }, 5.0);
    polyline->set_close(true);
    polyline->set_pos(center);
    // polyline->set_anchor({ 0.5, 0.5 });
    // polyline->set_scale({ 2, 1 });
    polyline->set_draw_bounds(true);
    polyline->set_draw_anchor(true);
    // polyline->set_rotation(1);
    renderer.add_item(polyline);

    std::shared_ptr<GfxPrimitive2D> selected = polyline;

    while (run)
    {
        renderer.draw_frame();
        set_color(curspp::color::WHITE);
        add_str({ 0, 0 }, "resolution: " + std::to_string(renderer.get_resolution().round().x) + "x" + std::to_string(renderer.get_resolution().round().y));
        add_str({ 0, 1 }, "radius: " + std::to_string(ellipse->get_radius().round().x) + "x" + std::to_string(ellipse->get_radius().round().y));
        add_str({ 0, 2 }, "pos: " + std::to_string(ellipse->get_pos().round().x) + "x" + std::to_string(ellipse->get_pos().round().y));

        switch (get_input())
        {
            case 'k':
                ellipse->set_radius(ellipse->get_radius() + Vec2d { 0, 1 });
                break;
            case 'j':
                ellipse->set_radius(ellipse->get_radius() - Vec2d { 0, 1 });
                break;

            case 'l':
                ellipse->set_radius(ellipse->get_radius() + Vec2d { 1, 0 });
                break;
            case 'h':
                ellipse->set_radius(ellipse->get_radius() - Vec2d { 1, 0 });
                break;

            case 'w':
                selected->set_pos(selected->get_pos() + Vec2d { 0, -1 });
                break;
            case 'a':
                selected->set_pos(selected->get_pos() + Vec2d { -1, 0 });
                break;
            case 's':
                selected->set_pos(selected->get_pos() + Vec2d { 0, 1 });
                break;
            case 'd':
                selected->set_pos(selected->get_pos() + Vec2d { 1, 0 });
                break;

            case 'L':
                selected->set_rotation(selected->get_rotation() + 0.05);
                break;
            case 'H':
                selected->set_rotation(selected->get_rotation() - 0.05);
                break;

            case 'i':
                selected->set_line_thickness(selected->get_line_thickness() - 1);
                break;
            case 'o':
                selected->set_line_thickness(selected->get_line_thickness() + 1);
                break;

            case 'f':
                ellipse->set_fill(!ellipse->get_fill());
                break;
            case 'b':
                selected->set_draw_bounds(!selected->get_draw_bounds());
                break;

            case 'r':
                renderer.remove_item(ellipse);
                break;
            case 'e':
                renderer.add_item(ellipse);
                break;

            case 'q':
                end();
                run = false;
                break;
       }
    }
}


