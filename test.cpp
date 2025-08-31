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

    coord2D screen_size = get_screen_size() * coord2D{ 4, 2 };
    coord2D center = screen_size / coord2D{ 4, 2 };

    GfxRender2D renderer(screen_size);

    coord2D radius = { 30, 15 };
    auto ellipse = renderer.create_ellipse(center - radius, radius, Color3 { 255, 0, 0 }, 5);

    while (run)
    {
        renderer.draw_frame();

        switch (get_input())
        {
            case 'k':
                ellipse->set_radius(ellipse->get_radius() + coord2D { 1, 1 });
                ellipse->set_position(center - ellipse->get_radius());
                break;
            case 'j':
                ellipse->set_radius(ellipse->get_radius() - coord2D { 1, 1 });
                ellipse->set_position(center - ellipse->get_radius());
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
