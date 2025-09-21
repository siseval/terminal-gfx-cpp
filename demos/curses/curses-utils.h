#ifndef DEMO_UTILS_H
#define DEMO_UTILS_H

#include <locale.h>
#include <string>
#include <ncurses.h>
#include <gfx/core/gfx-render-2D.h>
#include <gfx/math/vec2.h>

namespace demos
{

enum class default_color
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


inline gfx::math::Vec2i get_screen_size()
{
    int width, height;
    getmaxyx(stdscr, height, width);
    return { width, height };
}

inline char get_input()
{
    return getch();
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

inline void set_color(const enum default_color color)
{
    attron(COLOR_PAIR(color));
}

inline void add_str(const gfx::math::Vec2i pos, const std::string pixel)
{
    mvaddstr(pos.y, pos.x, pixel.data());
}

inline void init()
{
    setlocale(LC_ALL, "");

    initscr();
    timeout(0);
    nocbreak();
    noecho();
    curs_set(0);

    start_color();
    use_default_colors();

    init_pair(1, COLOR_BLACK, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_GREEN, -1);
    init_pair(4, COLOR_YELLOW, -1);
    init_pair(5, COLOR_BLUE, -1);
    init_pair(6, COLOR_MAGENTA, -1);
    init_pair(7, COLOR_CYAN, -1);
    init_pair(8, COLOR_WHITE, -1);
}

inline void end()
{
    endwin();
    exit(0);
}

}

#endif // DEMO_UTILS_H
