#ifndef DEMO_PLAYER_H
#define DEMO_PLAYER_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>

namespace demos::common::core
{

class DemoPlayer
{

public:

    DemoPlayer() : renderer(std::shared_ptr<gfx::core::GfxRender2D>()) {}

    void init();
    void run();

protected:

    void cycle_demo(const int direction);
    void handle_input(const char input);
    std::vector<std::string> get_info();

    virtual char get_input() = 0;
    virtual void draw_info() = 0;

    std::shared_ptr<gfx::core::GfxRender2D> renderer;
    std::vector<std::shared_ptr<GfxDemo>> demos;
    int current_demo = 0;

    bool show_info = true;
    bool show_debug = false;

    bool running = true;

};

}

#endif // DEMO_PLAYER_H
