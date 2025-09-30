#ifndef INTERACTIVE_DEMO_H
#define INTERACTIVE_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>

namespace demos::common::interactive
{

class InteractiveDemo : public demos::common::core::GfxDemo
{

public:

    InteractiveDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer) {}

    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const char input) override;

private:

    std::vector<std::shared_ptr<gfx::core::GfxPrimitive2D>> items;
    int selected_index = -1;

    void select(int index);
    void remove_selected();

    void add_circle(const bool child);
    void add_ellipse(const bool child = false);
    void add_polyline(const bool child = false);

    inline std::shared_ptr<gfx::core::GfxPrimitive2D> get_selected() 
    { 
        if (items.size() <= 0 || selected_index < 0 || selected_index >= static_cast<int>(items.size())) 
        { 
            return nullptr; 
        }
        return items[selected_index]; 
    }

};

}

#endif // INTERACTIVE_DEMO_H
