#ifndef CURSPP_H
#define CURSPP_H

#include <string>
#include <curses.h>
#include <locale>
#include <cstdint>
#include "vec2.h"


namespace curspp {


enum class color
{
    BLACK = 1,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    MAGENTA,
    CYAN,
    WHITE,
};

typedef int32_t coord_type;
typedef curspp::Vec2<coord_type> coord2D;

constexpr coord2D UP = coord2D { 0, -1 };
constexpr coord2D DOWN = coord2D { 0, 1 };
constexpr coord2D LEFT = coord2D { -1, 0 };
constexpr coord2D RIGHT = coord2D { 1, 0 };

void init();
void end();

inline void add_str(const coord2D pos, const std::string pixel)
{
    mvaddstr(pos.y, pos.x, pixel.data());
}

inline void set_color(const enum color color)
{
    attron(COLOR_PAIR(color));
}

inline void set_bold(const bool enable)
{
    if (enable)
    {
        attron(A_BOLD);
    }
    else
    {
        attroff(A_BOLD);
    }
}

inline coord2D get_screen_size()
{
    coord_type width, height;
    getmaxyx(stdscr, height, width);
    return { width, height };
}

inline coord2D get_cursor_pos()
{
    coord_type x, y;
    getyx(stdscr, y, x);
    return { x, y };
}

inline char get_input()
{
    return getch();
}

inline void flush_input()
{
    flushinp();
}

inline void set_timeout_ms(coord_type ms)
{
    timeout(ms);
}

inline void refresh()
{
    refresh();
}

inline void clear_screen()
{
    erase();
}

}
#endif // CURSPP_H
