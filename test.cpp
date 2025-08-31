#include "curspp.h"
#include "curspp-draw.h"
#include "curspp-graphics.h"

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
    set_bold(true);
    bool run = true;

    int16_t num_points = 700;
    double distance_factor = 0.4;
    double rotation = 0.0;

    init();
    clear_screen();

    vec2c screen_size = get_screen_size() * vec2c { 4, 2 };
    vec2c center = screen_size / vec2c { 4, 2 };
    coord_type distance = std::min(screen_size.x, screen_size.y) * distance_factor;

    std::vector<vec2c> positions;

    auto gfx_context = create_context(screen_size);

    for (uint8_t dr = 0; dr < 10; dr++)
    {
        for (uint16_t i = 0; i <= num_points; i++)
        {
            double theta = -(M_PI / 2) + (static_cast<double>(i) / num_points) * (2 * M_PI);
            coord_type x = static_cast<coord_type>(std::round(cos(theta + rotation) * (distance - dr) * 1));
            coord_type y = static_cast<coord_type>(std::round(sin(theta + rotation) * (distance - dr)));
            vec2c pos = { x, y };

            positions.push_back(center + pos);
        }
    }

    Color3 color = { 0, 255, 50 };
        
    set_pixel(gfx_context, center, color);
    for (vec2c pos : positions)
    {
            // draw_line(center, pos, "·");
        set_pixel(gfx_context, pos, Color3{ 255, 255, 255 });
    }

    while (run)
    {
        draw_frame(gfx_context);

        // draw_points(positions, "•", color::YELLOW);

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

        vec2c screen_size = get_screen_size();
        vec2c center = screen_size / 2;
        coord_type distance = std::min(screen_size.x, screen_size.y) * distance_factor;

        std::vector<vec2c> positions;

        for (uint16_t i = 0; i <= num_points; i++)
        {
            double theta = -(M_PI / 2) + (static_cast<double>(i) / num_points) * (2 * M_PI);
            coord_type x = static_cast<coord_type>(std::round(cos(theta + rotation) * distance * 2));
            coord_type y = static_cast<coord_type>(std::round(sin(theta + rotation) * distance));
            vec2c pos = { x, y };

            positions.push_back(center + pos);
        }

        for (vec2c pos : positions)
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
