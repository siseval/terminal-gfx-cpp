#ifndef POLYLINE_DEMO_H
#define POLYLINE_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <common/gfx-demo.h>

namespace demos::common::animations
{

class PolylineDemo : public GfxDemo
{

public:

    PolylineDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer) {}

    void init() override;
    void render_frame() override;
    void end() override;
    void handle_input(const char input) override {}

private:

    int num_polylines = 32;
    std::vector<std::shared_ptr<gfx::primitives::Polyline2D>> polylines;

};

}

#endif // POLYLINE_DEMO_H
