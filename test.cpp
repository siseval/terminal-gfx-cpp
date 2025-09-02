#include "curspp.h"
#include "curspp-draw.h"
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

    coord2D screen_size = get_screen_size() * 2;

    GfxRender2D renderer(screen_size);
    coord2D center = renderer.get_center();

    coord2D radius = { 30, 30 };
    auto ellipse = renderer.create_ellipse(center, radius, Color3 { 240, 240, 20 }, 3);
    ellipse->set_anchor({ 0.5, 0.5 });
    ellipse->set_pos(center);
    // renderer.add_item(ellipse);

    std::vector<coord2D> points = { center - coord2D { 40, 37 }, center + coord2D { 0, 30 }, center + coord2D { 30, -30 }, center - coord2D { 40, 37 } };
    auto polyline = renderer.create_polyline(points, Color3 { 20, 20, 240 }, 5.0);
    renderer.add_item(polyline);

    while (run)
    {
        renderer.draw_frame();

        switch (get_input())
        {
            case 'k':
                ellipse->set_radius(ellipse->get_radius() + coord2D { 0, 1 });
                break;
            case 'j':
                ellipse->set_radius(ellipse->get_radius() - coord2D { 0, 1 });
                break;

            case 'l':
                ellipse->set_radius(ellipse->get_radius() + coord2D { 1, 0 });
                break;
            case 'h':
                ellipse->set_radius(ellipse->get_radius() - coord2D { 1, 0 });
                break;

            case 'L':
                ellipse->set_rotation(ellipse->get_rotation() + 0.05);
                break;
            case 'H':
                ellipse->set_rotation(ellipse->get_rotation() - 0.05);
                break;

            case 'f':
                ellipse->set_fill(!ellipse->get_fill());
                break;
            case 'b':
                ellipse->set_draw_bounds(!ellipse->get_draw_bounds());
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

void circle_test()
{
    bool run = true;

    int16_t num_points = 16;
    double distance_factor = 0.4;
    double rotation = 0.0;

    init();
    while (run)
    {
        clear_screen();

        coord2D screen_size = get_screen_size();
        coord2D center = screen_size / 2;
        coord_type distance = std::min(screen_size.x, screen_size.y) * distance_factor;

        std::vector<coord2D> positions;

        for (uint16_t i = 0; i <= num_points; i++)
        {
            double theta = -(M_PI / 2) + (static_cast<double>(i) / num_points) * (2 * M_PI);
            coord_type x = static_cast<coord_type>(std::round(cos(theta + rotation) * distance * 2));
            coord_type y = static_cast<coord_type>(std::round(sin(theta + rotation) * distance));
            coord2D pos = { x, y };

            positions.push_back(center + pos);
        }

        for (coord2D pos : positions)
        {
             draw_line(center, pos, "·");
        }

        draw_point(center, "O", color::YELLOW);
        draw_points(positions, "•", color::YELLOW);

        switch (get_input())
        {
            case 'q':
                end();
                run = false;
                break;

            case '1':
                distance_factor -= 0.03;
                break;
            case '2':
                distance_factor += 0.03;
                break;

            case '3':
                num_points--;
                break;
            case '4':
                num_points++;
                break;

            case '5':
                rotation -= 0.03;
                break;
            case '6':
                rotation += 0.03;
                break;
        }
    }

}
