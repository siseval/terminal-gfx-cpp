#include <algorithm>
#include <demos/common/animations/space/camera.h>
#include <demos/common/core/demo-utils.h>

namespace demos::common::animations::space
{

using namespace gfx::math;
using namespace demos::common::core;

void Camera::process(const double dt)
{
    if (state == State::Transitioning)
    {
        do_transition(dt);
    }
    else if (state == State::Tracking)
    {
        do_track(dt);
    }
    else
    {
        do_free(dt);
    }
}

void Camera::handle_input(const char input)
{
    switch (input)
    {
        case 'w':
            state = State::Free;
            smooth_pan({ 0, -1 });
            break;

        case 's':
            state = State::Free;
            smooth_pan({ 0, 1 });
            break;

        case 'a':
            state = State::Free;
            smooth_pan({ -1, 0 });
            break;

        case 'd':
            state = State::Free;
            smooth_pan({ 1, 0 });
            break;

        case 'k':
            smooth_zoom(0.25);
            break;

        case 'j':
            smooth_zoom(2.0);
            break;
    }
}

void Camera::smooth_pan(const Vec2d direction)
{
    velocity += direction * pan_speed * size_cur.length();
}

void Camera::smooth_zoom(const double factor)
{
    zoom_velocity += (factor - 1.0) * 0.1;
}

void Camera::do_transition(const double dt)
{
    track_time += dt;
    const double t { std::clamp(track_time / track_duration, 0.0, 1.0) };

    cur_pos = Vec2d::lerp(start_pos, end_pos, utils::ease_in_out_cubic(t));

    if (t < 0.5)
    {
        const double zoom_t { utils::ease_in_out_cubic(t * 2.0) };
        size_cur = std::lerp(size0.x, zoom_out_size.x, zoom_t);
    }
    else
    {
        const double zoom_t { utils::ease_in_out_cubic((t - 0.5) * 2.0) };
        size_cur = std::lerp(zoom_out_size.x, size1.x, zoom_t);
    }
    if (t >= 1.0)
    {
        state = State::Tracking;
    }
}

void Camera::do_track(const double dt)
{
    cur_pos = end_pos;
    zoom_velocity *= std::pow(0.5, dt);
    size_cur.x *= 1 + zoom_velocity * dt;
}

void Camera::do_free(const double dt)
{
    velocity *= std::pow(0.3, dt);
    cur_pos += velocity * dt;
    zoom_velocity *= std::pow(0.5, dt);
    size_cur.x *= 1 + zoom_velocity * dt;
}

}
