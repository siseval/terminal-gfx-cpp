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
    demo.set_camera_pos({ 0, 0 });
    demo.set_camera_size(4.0e11);

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
    demo.set_camera_pos({ 0, 0 });
    demo.set_camera_size(1.0e13);

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

void chaos(SpaceDemo &demo)
{
    demo.set_camera_pos({ 0, 0 });
    demo.set_camera_size(1.0e10);

    demo.spawn_body(
        "core",
        { 0.0, 0.0 },
        { 0.0, 0.0 },
        1.0e7,
        1.0e26,
        false,
        { 1.0, 0.6, 0.0, 1.0 }
    );

    demo.spawn_body("body_1", { 5.0e7, 0.0 },       { 0.0, 1.2e4 }, 2.0e6, 1.0e22, { 0.8, 0.2, 0.2, 1.0 });
    demo.spawn_body("body_2", { -6.0e7, 2.0e7 },     { -1.0e4, -0.8e4 }, 1.8e6, 8.0e21, { 0.2, 0.8, 0.3, 1.0 });
    demo.spawn_body("body_3", { 0.0, -8.0e7 },       { 1.4e4, 0.0 }, 1.5e6, 9.0e21, { 0.4, 0.4, 1.0, 1.0 });
    demo.spawn_body("body_4", { 3.0e7, 4.0e7 },      { -0.7e4, 1.1e4 }, 1.0e6, 6.0e21, { 0.9, 0.9, 0.2, 1.0 });
    demo.spawn_body("body_5", { -2.5e7, -3.5e7 },    { 0.9e4, -0.6e4 }, 1.2e6, 7.0e21, { 0.6, 0.1, 0.9, 1.0 });
    demo.spawn_body("body_6", { 1.0e7, -1.5e7 },     { 1.2e4, 0.8e4 }, 1.4e6, 7.5e21, { 0.2, 0.7, 1.0, 1.0 });
    demo.spawn_body("body_7", { -1.2e7, 1.8e7 },     { -1.0e4, 0.5e4 }, 1.1e6, 5.5e21, { 1.0, 0.3, 0.6, 1.0 });
    demo.spawn_body("body_8", { 2.2e7, -2.0e7 },     { 0.5e4, -1.3e4 }, 1.3e6, 6.2e21, { 0.3, 1.0, 0.8, 1.0 });
    demo.spawn_body("body_9", { -2.0e7, 2.5e7 },     { 0.7e4, 1.0e4 }, 1.0e6, 5.8e21, { 0.5, 0.5, 0.5, 1.0 });
    demo.spawn_body("body_10",{ 4.0e7, -1.0e7 },     { -1.1e4, 1.0e4 }, 1.5e6, 8.5e21, { 1.0, 0.8, 0.6, 1.0 });

    demo.spawn_body("frag_1", { 3.0e6, 0.0 },        { 0.0, 1.8e4 }, 5.0e5, 5.0e20, { 0.7, 0.7, 1.0, 1.0 });
    demo.spawn_body("frag_2", { -4.0e6, 1.0e6 },     { -1.5e4, -1.2e4 }, 4.0e5, 4.5e20, { 0.6, 0.4, 0.9, 1.0 });
    demo.spawn_body("frag_3", { 0.0, 5.0e6 },        { 1.7e4, 0.0 }, 3.5e5, 3.8e20, { 0.3, 0.6, 0.9, 1.0 });
    demo.spawn_body("frag_4", { -2.0e6, -3.0e6 },    { 1.2e4, -1.1e4 }, 3.0e5, 3.0e20, { 0.8, 0.4, 0.4, 1.0 });

    demo.spawn_body("flyby", { -1.0e8, -1.0e8 },     { 5.0e4, 6.0e4 }, 2.0e6, 1.0e22, { 0.9, 1.0, 0.9, 1.0 });
}

}
