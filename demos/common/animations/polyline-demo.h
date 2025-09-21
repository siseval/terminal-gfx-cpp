#ifndef POLYLINE_DEMO_H
#define POLYLINE_DEMO_H

#include <gfx/core/gfx-render-2D.h>
#include <gfx/surfaces/curses-render-surface.h>

namespace demos::animations
{

class PolylineDemo : public GfxDemo
{

public:

    void render_frame() override;

};

}

#endif // POLYLINE_DEMO_H
