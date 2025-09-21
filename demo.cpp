#include <ncurses.h>
#include <string>
#include <locale.h>
#include <gfx/core/gfx-render-2D.h>
#include <gfx/surfaces/curses-render-surface.h>


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

using namespace gfx::core;
using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;

void gfx_test();
void circle_test();

Vec2i get_screen_size();
char get_input();
void set_bold(const bool enable);
void set_color(const enum default_color color);
void add_str(const Vec2i pos, const std::string pixel);

void init();
void end();

int main()
{
    std::srand(std::time(0));
    init();
    gfx_test();
    end();
    return 0;
}

void select(int index, std::shared_ptr<GfxPrimitive2D>& selected, std::vector<std::shared_ptr<GfxPrimitive2D>> items, std::shared_ptr<GfxRender2D> renderer)
{
    if (items.size() <= 0)
    {
        selected = nullptr;
        return;
    }
    if (selected != nullptr)
    {
        selected->set_draw_aabb(false);
        selected->set_depth(1);
    }
    selected = items[index];
    selected->set_draw_aabb(true);
    selected->set_depth(0);
}

void gfx_test()
{
    set_bold(true);
    bool run = true;

    Vec2d screen_size = get_screen_size() * 2;

    auto renderer = std::make_shared<GfxRender2D>(std::make_shared<gfx::surfaces::CursesRenderSurface>(screen_size), Vec2d { 2, 1 });
    Vec2d center = renderer->center();

    std::vector<std::shared_ptr<GfxPrimitive2D>> items;

    int index = 0;
    std::shared_ptr<GfxPrimitive2D> selected = nullptr;

    Color4 color;
    std::shared_ptr<Ellipse2D> ellipse;
    std::shared_ptr<Polyline2D> polyline;

    while (run)
    {
        renderer->draw_frame();
        set_color(default_color::WHITE);

        if (selected != nullptr)
        {
            add_str({ 0, 0 }, "resolution: " + std::to_string(renderer->get_resolution().round().x) + "x" + std::to_string(renderer->get_resolution().round().y));
            add_str({ 0, 1 }, "items: " + std::to_string(renderer->num_items()));
            add_str({ 0, 2 }, "pos: " + std::to_string(selected->get_pos().round().x) + "x" + std::to_string(selected->get_pos().round().y));
        }

        switch (get_input())
        {
            case 'q':
                end();
                run = false;
                break;

            // case 'k':
            //     ellipse->set_radius(ellipse->get_radius() + Vec2d { 0, 1 });
            //     break;
            // case 'j':
            //     ellipse->set_radius(ellipse->get_radius() - Vec2d { 0, 1 });
            //     break;
            //
            // case 'l':
            //     ellipse->set_radius(ellipse->get_radius() + Vec2d { 1, 0 });
            //     break;
            // case 'h':
            //     ellipse->set_radius(ellipse->get_radius() - Vec2d { 1, 0 });
            //     break;

            case 'k':
                if (selected == nullptr) { break; }
                selected->set_scale(selected->get_scale() + Vec2d { 0, 0.05 });
                break;
            case 'j':
                if (selected == nullptr) { break; }
                selected->set_scale(selected->get_scale() - Vec2d { 0, 0.05 });
                break;

            case 'l':
                if (selected == nullptr) { break; }
                selected->set_scale(selected->get_scale() + Vec2d { 0.05, 0 });
                break;
            case 'h':
                if (selected == nullptr) { break; }
                selected->set_scale(selected->get_scale() - Vec2d { 0.05, 0 });
                break;

            case 'w':
                if (selected == nullptr) { break; }
                selected->set_pos(selected->get_pos() + Vec2d { 0, -1 });
                break;
            case 'a':
                if (selected == nullptr) { break; }
                selected->set_pos(selected->get_pos() + Vec2d { -1, 0 });
                break;
            case 's':
                if (selected == nullptr) { break; }
                selected->set_pos(selected->get_pos() + Vec2d { 0, 1 });
                break;
            case 'd':
                if (selected == nullptr) { break; }
                selected->set_pos(selected->get_pos() + Vec2d { 1, 0 });
                break;

            case 'L':
                if (selected == nullptr) { break; }
                selected->set_rotation(selected->get_rotation() + 0.05);
                break;
            case 'H':
                if (selected == nullptr) { break; }
                selected->set_rotation(selected->get_rotation() - 0.05);
                break;

            case 'i':
                if (selected == nullptr) { break; }
                selected->set_line_thickness(selected->get_line_thickness() - 1);
                break;
            case 'o':
                if (selected == nullptr) { break; }
                selected->set_line_thickness(selected->get_line_thickness() + 1);
                break;

            case 'f':
                if (selected == nullptr) { break; }
                selected->set_fill(!selected->get_fill());
                break;

            case 'b':
                if (selected == nullptr) { break; }
                selected->set_draw_aabb(!selected->get_draw_aabb());
                break;
            case 'B':
                if (selected == nullptr) { break; }
                selected->set_draw_obb(!selected->get_draw_obb());
                break;

            case 'n':
                select((index += 1) %= items.size(), selected, items, renderer);
                break;

            case 'r':
                if (selected == nullptr) { break; }
                renderer->remove_item(selected);
                items.erase(std::remove(items.begin(), items.end(), selected));
                select((index -= 1) %= items.size(), selected, items, renderer);
                break;
                
            case 'e':
                color = { std::rand() % 255, std::rand() % 255, std::rand() % 255 };
                ellipse = renderer->create_ellipse(center, { 10, 10 }, color, 3);
                ellipse->set_anchor({ 0.5, 0.5 });
                items.push_back(ellipse);
                select(index = items.size() - 1, selected, items, renderer);
                renderer->add_item(ellipse);
                break;

            case 't':
                color = { std::rand() % 255, std::rand() % 255, std::rand() % 255 };
                polyline = renderer->create_polyline(center, { { 0, 0 }, { 20, 0 }, { 10, 10} }, color, 3);
                polyline->set_close(true);
                polyline->set_rounded_corners(true);
                polyline->set_anchor({ 0.5, 0.5 });
                items.push_back(polyline);
                select(index = items.size() - 1, selected, items, renderer);
                renderer->add_item(polyline);
                break;

            case 'E':
                color = { std::rand() % 255, std::rand() % 255, std::rand() % 255 };
                ellipse = renderer->create_ellipse({ 0, 0 }, { 10, 10 }, color, 3);
                ellipse->set_anchor({ 0.5, 0.5 });
                items.push_back(ellipse);
                renderer->add_item(ellipse, selected);
                select(index = items.size() - 1, selected, items, renderer);
                break;

            case 'T':
                color = { std::rand() % 255, std::rand() % 255, std::rand() % 255 };
                polyline = renderer->create_polyline({ 0, 0 }, { { 0, 0 }, { 20, 0 }, { 10, 10} }, color, 3);
                polyline->set_close(true);
                polyline->set_rounded_corners(true);
                polyline->set_anchor({ 0.5, 0.5 });
                items.push_back(polyline);
                renderer->add_item(polyline, selected);
                select(index = items.size() - 1, selected, items, renderer);
                break;


       }
    }
}

Vec2i get_screen_size()
{
    int width, height;
    getmaxyx(stdscr, height, width);
    return { width, height };
}

char get_input()
{
    return getch();
}

void set_bold(const bool enable)
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

void set_color(const enum default_color color)
{
    attron(COLOR_PAIR(color));
}

void add_str(const Vec2i pos, const std::string pixel)
{
    mvaddstr(pos.y, pos.x, pixel.data());
}

void init()
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

void end()
{
    endwin();
    exit(0);
}
