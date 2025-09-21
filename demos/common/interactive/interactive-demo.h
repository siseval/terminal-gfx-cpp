#ifndef INTERACTIVE_DEMO_H
#define INTERACTIVE_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <common/gfx-demo.h>

namespace demos::common::interactive
{

class InteractiveDemo : public GfxDemo
{

public:

    InteractiveDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer) 
    {
        init();
    }

    void init() override;
    void render_frame() override;
    void handle_input(const char input) override;
    void end() override;
    std::vector<std::string> info_text() override;

private:

    std::vector<std::shared_ptr<gfx::core::GfxPrimitive2D>> items;
    int selected_index = -1;

    double last_frame_time = 0.0;

    void select(int index);
    void remove_selected();
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
