#ifndef TEXT_DEMO_H
#define TEXT_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>

namespace demos::common::animations::text
{

class TextDemo : public demos::common::core::GfxDemo
{

public:

    TextDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer) {}

    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const int input) override;
    void report_mouse(const demos::common::core::MouseEvent event) override {}

    std::vector<std::string> debug_text() override
    {
        return { 
            "num points: " + std::to_string(num_points)
        };
    }

private:

    int num_points { 0 };

};

}

#endif // TEXT_DEMO_H
