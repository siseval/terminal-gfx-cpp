#include <gfx/core/gfx-render-2D.h>
#include <gfx/surfaces/curses-render-surface.h>
#include <curses/curses-utils.h>
#include <common/animations/star-demo.h>
#include <common/animations/snake-demo.h>

namespace demos::curses::animations
{

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;
using namespace gfx::surfaces;
using namespace demos::common::animations;
using namespace demos::common;

class AnimationDemoPlayer
{

public:

    AnimationDemoPlayer() : demos(std::vector<std::shared_ptr<GfxDemo>>()) {}

    void init()
    {
        renderer = std::make_shared<GfxRender2D>(std::make_shared<CursesRenderSurface>(get_screen_size() * 2), Vec2d { 2, 1 });

        demos.push_back(std::make_shared<StarDemo>(renderer));
        demos.push_back(std::make_shared<SnakeDemo>(renderer));

        demos[current_demo]->init();
    }

    void run()
    {
        while (running)
        {
            demos[current_demo]->render_frame();

            if (show_info)
            {
                set_color(default_color::WHITE);
                draw_info();
            }

            char input = get_input();
            demos[current_demo]->handle_input(input);
            handle_input(input);
        }
        end();
    }


private:

    std::shared_ptr<GfxRender2D> renderer;
    std::vector<std::shared_ptr<GfxDemo>> demos;
    int current_demo = 0;

    bool show_info = true;
    bool show_debug = false;

    bool running = true;


    void draw_info()
    {
        std::vector<std::string> info = demos[current_demo]->info_text();

        if (show_debug)
        {
            info.push_back("");
            for (const auto &line : demos[current_demo]->debug_text())
            {
                info.push_back(line);
            }
        }

        info.push_back("");
        info.push_back("[p/n] to cycle (" + std::to_string(current_demo + 1) + "/" + std::to_string(demos.size()) + ")");
        info.push_back("[q] to quit");

        for (int i = 0; i < info.size(); i++)
        {
            add_str({ 0, i }, info[i]);
        }
    }

    void cycle_demo(const int direction)
    {
        current_demo = (current_demo + direction + demos.size()) % demos.size();
        renderer->clear_items();
        demos[current_demo]->init();
    }

    void handle_input(const char input)
    {
        switch (input)
        {
            case 'q':
                running = false;
                break;
            case 'u':
                show_info = !show_info;
                break;
            case 'd':
                show_debug = !show_debug;
                break;
            case 'n':
                cycle_demo(1);
                break;
            case 'p':
                cycle_demo(-1);
                break;
        }
    }


};

}

int main()
{
    demos::curses::init();
    demos::curses::set_bold(true);

    demos::curses::animations::AnimationDemoPlayer player;
    player.init();
    player.run();
}
