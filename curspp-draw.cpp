#include "curspp-draw.h"

namespace curspp
{
 
void draw_point(const coord2D point, const std::string pixel, const curspp::color color)
{
    set_color(color);
    add_str(point, pixel);
}

void draw_points(const std::vector<coord2D> points, const std::string pixel, const curspp::color color)
{
    set_color(color);
    for (coord2D point : points)
    {
         add_str(point, pixel);
    }
}

void draw_line(const coord2D start, const coord2D end, const std::string pixel, const curspp::color color)
{
    coord_type delta_x = std::abs(end.x - start.x);
    int8_t sign_x = start.x < end.x ? 1 : - 1;

    coord_type delta_y = -std::abs(end.y - start.y);
    int8_t sign_y = start.y < end.y ? 1 : - 1;

    coord_type error = delta_x + delta_y;
    coord2D cur_pos = start;

    while (true)
    {
        add_str(cur_pos, pixel);
        coord_type error_doubled = 2 * error;

        if (error_doubled >= delta_y)
        {
            if (cur_pos.x == end.x)
            {
                break;
            }
            error += delta_y;
            cur_pos.x += sign_x;
        }
        if (error_doubled <= delta_x)
        {
            if (cur_pos.y == end.y)
            {
                break;
            }
            error += delta_x;
            cur_pos.y += sign_y;
        }
    }

    set_color(color);
}

}
