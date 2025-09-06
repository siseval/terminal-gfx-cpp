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

constexpr Vec2i UP = Vec2i { 0, -1 };
constexpr Vec2i DOWN = Vec2i { 0, 1 };
constexpr Vec2i LEFT = Vec2i { -1, 0 };
constexpr Vec2i RIGHT = Vec2i { 1, 0 };

void init();
void end();

inline void add_str(const Vec2i pos, const std::string pixel)
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

inline Vec2i get_screen_size()
{
    int width, height;
    getmaxyx(stdscr, height, width);
    return { width, height };
}

inline Vec2i get_cursor_pos()
{
    int x, y;
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

inline void set_timeout_ms(int ms)
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
