#include "curspp.h"
#include "curspp-draw.h"

int main()
{
    bool run = true;

    int16_t num_points = 16;
    double distance_factor = 0.4;
    double rotation = 0.0;

    curspp::init();
    while (run)
    {
        curspp::clear_screen();

        curspp::pos2 screen_size = curspp::get_screen_size();
        curspp::pos2 center = screen_size / 2;
        curspp::pos_type distance = std::min(screen_size.x, screen_size.y) * distance_factor;

        std::vector<curspp::pos2> positions;

        for (uint16_t i = 0; i <= num_points; i++)
        {
            double theta = -(M_PI / 2) + (static_cast<double>(i) / num_points) * (2 * M_PI);
            curspp::pos_type x = static_cast<curspp::pos_type>(std::round(cos(theta + rotation) * distance * 2));
            curspp::pos_type y = static_cast<curspp::pos_type>(std::round(sin(theta + rotation) * distance));
            curspp::pos2 pos = { x, y };

            positions.push_back(center + pos);
        }

        for (curspp::pos2 pos : positions)
        {
             curspp::draw_line(center, pos, "·");
        }

        curspp::draw_point(center, "O", curspp::YELLOW);
        curspp::draw_points(positions, "•", curspp::YELLOW);

        switch (curspp::get_input())
        {
            case 'q':
                curspp::end();
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
