#ifndef CAMERA_H
#define CAMERA_H

#include <gfx/math/vec2.h>

namespace demos::common::animations::space
{

class Camera
{
    
public:

    enum class State
    {
        Free,
        Transitioning,
        Tracking
    };

    void process(const double dt);

    void handle_input(const int input);

    void smooth_pan(const gfx::math::Vec2d direction);
    void smooth_zoom(const double factor);

    void do_transition(const double dt);
    void do_track(const double dt);
    void do_free(const double dt);

    State state { State::Free };

    double pan_speed { 0.1 };
    double zoom_velocity { 0.0 };
    double track_time { 0.0 };

    gfx::math::Vec2d velocity { 0.0, 0.0 };
    gfx::math::Vec2d zoom_out_size { 0.0, 0.0 };

    gfx::math::Vec2d start_pos { 0.0, 0.0 };
    gfx::math::Vec2d size0 { 0.0, 0.0 };
    gfx::math::Vec2d end_pos { 0.0, 0.0 };
    gfx::math::Vec2d size1 { 0.0, 0.0 };

    gfx::math::Vec2d cur_pos { 0.0, 0.0 };
    gfx::math::Vec2d size_cur { 0.0, 0.0 };

    double track_duration { 2.5 };

};

}

#endif // CAMERA_H
