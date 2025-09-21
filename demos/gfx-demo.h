#ifndef GFX_DEMO_H
#define GFX_DEMO_H

namespace demos
{

class GfxDemo
{

public:

    virtual void render_frame() = 0;
    virtual void handle_input(char input) = 0;

};

}

#endif // GFX_DEMO_H
