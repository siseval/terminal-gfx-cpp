#include <demos/curses/curses-demo-player.h>
#include <demos/curses/curses-utils.h>

int main()
{
    demos::curses::init();
    demos::curses::set_bold(true);

    demos::curses::CursesDemoPlayer player;
    player.init();
    player.run();

    demos::curses::end();
}
