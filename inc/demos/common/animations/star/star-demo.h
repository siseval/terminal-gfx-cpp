#ifndef STAR_DEMO_H
#define STAR_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>

namespace demos::common::animations::star
{

class StarDemo : public demos::common::core::GfxDemo
{

public:

    StarDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer) {}

    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const char input) override;

private:

    int num_polylines = 32;
    std::vector<std::shared_ptr<gfx::primitives::Polyline2D>> polylines;

};

}

#endif // STAR_DEMO_H
