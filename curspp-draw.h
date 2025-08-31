#ifndef CURSPP_DRAW_H
#define CURSPP_DRAW_H

#include "curspp.h"
#include <vector>

namespace curspp
{

void draw_point(const coord2D point, const std::string pixel, const curspp::color color = curspp::color::WHITE);
void draw_points(const std::vector<coord2D> points, const std::string pixel, const curspp::color color = curspp::color::WHITE);

void draw_line(const coord2D start, const coord2D end, const std::string pixel, const curspp::color color = curspp::color::WHITE);

}

#endif // CURSPP_DRAW_H
