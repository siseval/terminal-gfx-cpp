#ifndef CURSPP_H
#define CURSPP_H

#include <string>
#include <curses.h>
#include <locale>
#include <cstdint>
#include "vec2.h"


namespace curspp {

typedef int32_t pos_type;
typedef vec2::Vec2<pos_type> vec2c;

struct color3
{
    int8_t r;
    int8_t g;
    int8_t b;
};

enum class color
{
    BLACK = 1,
    RED = 2,
    GREEN = 3,
    YELLOW = 4,
    BLUE = 5,
    MAGENTA = 6,
    WHITE = 7,
};
using color = enum color;

constexpr vec2c UP = vec2c{ 0, -1 };
constexpr vec2c DOWN = vec2c{ 0, 1 };
constexpr vec2c LEFT = vec2c{ -1, 0 };
constexpr vec2c RIGHT = vec2c{ 1, 0 };

void init();
void end();

inline void add_str(const vec2c pos, const std::string pixel)
{
    mvaddstr(pos.y, pos.x, pixel.data());
}

inline void set_color(const enum color c)
{
    attron(COLOR_PAIR(c));
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

inline vec2c get_screen_size()
{
    pos_type width, height;
    getmaxyx(stdscr, height, width);
    return { width, height };
}

inline vec2c get_cursor_pos()
{
    pos_type x, y;
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

inline void set_timeout_ms(pos_type ms)
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
