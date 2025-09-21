#include <gfx/core/gfx-render-2D.h>
#include <gfx/surfaces/curses-render-surface.h>
#include <curses/curses-utils.h>
#include <common/interactive/interactive-demo.h>

namespace demos::curses::interactive
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;
using namespace gfx::surfaces;
using namespace demos::common::interactive;

void run()
{
    init();
    set_bold(true);

    auto surface = std::make_shared<CursesRenderSurface>(get_screen_size() * 2);
    InteractiveDemo demo(std::make_shared<gfx::core::GfxRender2D>(surface, Vec2d { 2, 1 }));

    bool running = true;

    while (running)
    {
        clear();
        demo.render_frame();
        set_color(default_color::WHITE);
        std::vector<std::string> info = demo.info_text();
        for (int i = 0; i < info.size(); i++)
        {
            add_str({ 0, i }, info[i]);
        }
        refresh();

        char input = get_input();
        if (input == 'q')
        {
            running = false;
        }
        else
        {
            demo.handle_input(input);
        }
    }

    end();
}

}

int main()
{
    demos::curses::interactive::run();
}

