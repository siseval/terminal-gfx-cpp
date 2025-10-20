#ifndef PHYSICS_DEMO_H
#define PHYSICS_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <demos/common/core/gfx-demo.h>

namespace demos::common::animations::physics
{

class PhysicsDemo : public demos::common::core::GfxDemo
{

public:

    PhysicsDemo(const std::shared_ptr<gfx::core::GfxRender2D> renderer)
        : GfxDemo(renderer) {}

    void init() override;
    void render_frame(const double dt) override;
    void end() override;
    void handle_input(const int input) override;
    void report_mouse(const demos::common::core::MouseEvent event) override {}

private:

    int num_polylines = 32;
    std::vector<std::shared_ptr<gfx::primitives::Polyline2D>> polylines;

};

}

#endif // PHYSICS_DEMO_H
