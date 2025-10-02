#include <demos/common/animations/space/simulations.h>
#include <demos/common/animations/space/space-demo.h>
#include <demos/common/animations/space/units.h>

namespace demos::common::animations::space::simulations
{

using namespace gfx::core::types;
using namespace gfx::math;
using namespace demos::common::animations::space::units;

void three_body_problem(SpaceDemo &demo)
{
    demo.set_view_pos({ 0, 0 });
    demo.set_view_size(4.0e11);
    demo.set_zoom_out_pos(4.0e11 * 0.5);

    demo.spawn_body(
        "body 1",
        { -1.0e11, 0.0 },
        { 0.0, -1.2e4 },
        1.0e10,
        2.0e30,
        true,
        { 1.0, 0.5, 0.5, 1.0 }
    );

    demo.spawn_body(
        "body 2",
        { 1.0e11, 0.0 },
        { 0.0, 1.2e4 },
        1.0e10,
        2.0e30,
        true,
        { 0.5, 1.0, 0.5, 1.0 }
    );

    demo.spawn_body(
        "body 3",
        { 0.0, 1.5e11 },
        { -1.5e4, 0.0 },
        1.0e10,
        2.0e30,
        true,
        { 0.5, 0.5, 1.0, 1.0 }
    );
}

void solar_system(SpaceDemo &demo)
{
    demo.set_view_pos({ 0, 0 });
    demo.set_view_size(1.0e13);
    demo.set_zoom_out_pos(1.0e13 * 0.5);

    demo.spawn_body(
        "the sun",
        { 0.0, 0.0 },
        { 0.0, 0.0 },
        6.9634e8,
        1.98847e30,
        true,
        { 1.0, 1.0, 0.0, 1.0 }
    );

    demo.spawn_body(
        "mercury",
        { 0.387 * AU, 0.0 },
        { 0.0, 47.4e3 },
        2.4397e6,
        3.3011e23,
        { 0.7, 0.5, 0.5, 1.0 }
    );

    demo.spawn_body(
        "venus",
        { 0.723 * AU, 0.0 },
        { 0.0, 35.0e3 },
        6.0518e6,
        4.8675e24,
        { 1.0, 0.8, 0.6, 1.0 }
    );

    demo.spawn_body(
        "earth",
        { 1.0 * AU, 0.0 },
        { 0.0, 29.78e3 },
        6.371e6,
        5.97237e24,
        { 0.0, 0.0, 1.0, 1.0 }
    );

    demo.spawn_body(
        "mars",
        { 1.524 * AU, 0.0 },
        { 0.0, 24.077e3 },
        3.3895e6,
        6.4171e23,
        { 1.0, 0.5, 0.5, 1.0 }
    );

    demo.spawn_body(
        "jupiter",
        { 5.204 * AU, 0.0 },
        { 0.0, 13.07e3 },
        6.9911e7,
        1.8982e27,
        { 1.0, 0.7, 0.5, 1.0 }
    );

    demo.spawn_body(
        "saturn",
        { 9.582 * AU, 0.0 },
        { 0.0, 9.69e3 },
        5.8232e7,
        5.6834e26,
        { 1.0, 0.9, 0.5, 1.0 }
    );

    demo.spawn_body(
        "uranus",
        { 19.20 * AU, 0.0 },
        { 0.0, 6.81e3 },
        2.5362e7,
        8.6810e25,
        { 0.5, 1.0, 1.0, 1.0 }
    );

    demo.spawn_body(
        "neptune",
        { 30.05 * AU, 0.0 },
        { 0.0, 5.43e3 },
        2.4622e7,
        1.02413e26,
        { 0.5, 0.5, 1.0, 1.0 }
    );
}

}
