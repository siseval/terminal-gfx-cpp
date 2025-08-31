#ifndef GFX_PRIMITIVE_STORE_2D_H
#define GFX_PRIMITIVE_STORE_2D_H

#include "gfx-primitive-2D.h"
#include "ellipse-2D.h"

namespace curspp::graphics
{

class GfxPrimitiveStore2D
{
    public:

    std::vector<std::shared_ptr<GfxPrimitive2D>> items;
};

}

#endif // GFX_PRIMITIVE_STORE_2D_H
