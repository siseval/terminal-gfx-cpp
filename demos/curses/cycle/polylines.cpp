#include <gfx/core/gfx-render-2D.h>
#include <gfx/surfaces/curses-render-surface.h>
#include <demos/curses/curses-utils.h>

using namespace gfx::core;


int main()
{

}

void run()
{
    bool run = true;
    double start_time = static_cast<double>(clock());

    while ()
}

void handle_input()
{
    switch (get_input())
    {
        case 'q':
            end();
            run = false;
            break;
    }
}
