#ifndef CURSES_DEMO_PLAYER_H
#define CURSES_DEMO_PLAYER_H

#include <gfx/core/render-2D.h>
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
        renderer = std::make_shared<gfx::core::Render2D>(surface, gfx::math::Vec2d { 2, 1 });
    }

    gfx::math::Vec2i get_screen_size() override
    {
        return demos::curses::get_screen_size() * 2;
    }

    int get_input() override
    {
        int input { demos::curses::get_input() };
        if (input == KEY_MOUSE)
        {
            MEVENT e;
            if (getmouse(&e) == OK)
            {
                demos::common::core::MouseEvent event { curses_to_mouse_event(e) };
                demos[current_demo]->report_mouse(event);
            }
            refresh();
            return 0;
        }
        return input;
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

private:

    demos::common::core::MouseEvent curses_to_mouse_event(const MEVENT e)
    {
        demos::common::core::MouseEvent event;
        switch (e.bstate)
        {
            case BUTTON1_PRESSED:
                event.type = demos::common::core::MouseEventType::LEFT_DOWN;
                break;

            case BUTTON3_PRESSED:
                event.type = demos::common::core::MouseEventType::RIGHT_DOWN;
                break;

            case BUTTON4_PRESSED:
                event.type = demos::common::core::MouseEventType::SCROLL_UP;
                break;

            case BUTTON5_PRESSED:
                event.type = demos::common::core::MouseEventType::SCROLL_DOWN;
                break;

            case REPORT_MOUSE_POSITION:
                event.type = demos::common::core::MouseEventType::MOVE;
                break;

            default:
                break;
        }
        event.position = gfx::math::Vec2i { e.x, e.y } * 2 / renderer->get_viewport_scaling();
        return event;
    }

};

}

#endif // CURSES_DEMO_PLAYER_H
