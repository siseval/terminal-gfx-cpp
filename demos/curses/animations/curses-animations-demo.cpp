#include <gfx/core/gfx-render-2D.h>
#include <gfx/surfaces/curses-render-surface.h>
#include <curses/curses-utils.h>
#include <common/animations/polyline-demo.h>

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
        demos.push_back(std::make_shared<PolylineDemo>(renderer));

        for (auto& demo : demos)
        {
            demo->init();
        }
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

            handle_input();
        }
        end();
    }


private:

    std::shared_ptr<GfxRender2D> renderer;
    std::vector<std::shared_ptr<GfxDemo>> demos;
    int current_demo = 0;
    bool show_info = true;

    bool running = true;


    void draw_info()
    {
        std::vector<std::string> info = demos[current_demo]->info_text();
        info.push_back("");
        info.push_back("[p/n] to cycle (" + std::to_string(current_demo + 1) + "/" + std::to_string(demos.size()) + ")");
        info.push_back("[q] to quit");
        for (int i = 0; i < info.size(); i++)
        {
            add_str({ 0, i }, info[i]);
        }
    }

    void handle_input()
    {
        switch (get_input())
        {
            case 'q':
                running = false;
                break;
            case 'u':
                show_info = !show_info;
                break;
            case 'n':
                current_demo = (current_demo + 1) % demos.size();
                break;
            case 'p':
                current_demo = (current_demo - 1 + demos.size()) % demos.size();
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
