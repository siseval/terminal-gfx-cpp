#ifndef CURSPP_DRAW_H
#define CURSPP_DRAW_H

#include "curspp.h"
#include <vector>

namespace curspp
{

void draw_point(const vec2c point, const std::string pixel, const curspp::color color = curspp::color::WHITE);
void draw_points(const std::vector<vec2c> points, const std::string pixel, const curspp::color color = curspp::color::WHITE);

void draw_line(const vec2c start, const vec2c end, const std::string pixel, const curspp::color color = curspp::color::WHITE);

}

#endif // CURSPP_DRAW_H
