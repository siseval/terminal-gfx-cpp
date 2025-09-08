#include "curspp.h"
#include "gfx-render-2D.h"

using namespace curspp;
using namespace curspp::gfx;

void gfx_test();
void circle_test();

int main()
{
    gfx_test();
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
        selected->set_draw_bounds(false);
        selected->set_depth(1);
    }
    selected = items[index];
    selected->set_draw_bounds(true);
    selected->set_depth(0);
}

void gfx_test()
{
    init();
    set_bold(true);
    bool run = true;

    Vec2d screen_size = get_screen_size() * 2;

    auto renderer = std::make_shared<GfxRender2D>(screen_size);
    Vec2d center = renderer->center();

    std::vector<std::shared_ptr<GfxPrimitive2D>> items;

    int index = 0;
    std::shared_ptr<GfxPrimitive2D> selected = nullptr;

    Color3 color;
    std::shared_ptr<Ellipse2D> ellipse;
    std::shared_ptr<Polyline2D> polyline;

    while (run)
    {
        renderer->draw_frame();
        set_color(curspp::color::WHITE);

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
                selected->set_draw_bounds(!selected->get_draw_bounds());
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
                Color3 color = { std::rand() % 255, std::rand() % 255, std::rand() % 255 };
                polyline = renderer->create_polyline(center, { { 0, 0 }, { 20, 0 }, { 10, 10} }, color, 3);
                polyline->set_close(true);
                polyline->set_anchor({ 0.5, 0.5 });
                items.push_back(polyline);
                select(index = items.size() - 1, selected, items, renderer);
                renderer->add_item(polyline);
                break;


       }
    }
}


