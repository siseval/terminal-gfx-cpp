#ifndef CURSES_DEMO_PLAYER_H
#define CURSES_DEMO_PLAYER_H

#include <gfx/core/gfx-render-2D.h>
#include <gfx/surfaces/curses-render-surface.h>
#include <demos/common/core/demo-player.h>
#include <demos/curses/curses-utils.h>

namespace demos::curses
{

class CursesDemoPlayer : public demos::common::core::DemoPlayer
{

public:

    CursesDemoPlayer() : demos::common::core::DemoPlayer()
    {
        auto surface { std::make_shared<gfx::surfaces::CursesRenderSurface>(demos::curses::get_screen_size() * 2) };
        renderer = std::make_shared<gfx::core::GfxRender2D>(surface, gfx::math::Vec2d { 2, 1 });
    }

    gfx::math::Vec2i get_screen_size() override
    {
        return demos::curses::get_screen_size() * 2;
    }

    char get_input() override
    {
        return demos::curses::get_input();
    }

    void draw_info() override
    {
        demos::curses::set_bold(true);
        demos::curses::set_color(demos::curses::default_color::WHITE);
        std::vector<std::string> info = get_info();
        for (int i = 0; i < info.size(); ++i)
        {
            add_str({ 0, i }, info[i]);
        }
    }

};

}

#endif // CURSES_DEMO_PLAYER_H
