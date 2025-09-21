#ifndef GFX_SHADER_2D_H
#define GFX_SHADER_2D_H

#include <gfx/core/types/color4.h>
#include <gfx/math/vec2.h>

namespace gfx::core
{

struct shader_input_2D
{
    gfx::math::Vec2d uv;
    double t;
};

class Shader2D
{

public:

    virtual types::Color4 frag(const shader_input_2D input) const = 0;


private:



};

}

#endif // GFX_SHADER_2D_H
