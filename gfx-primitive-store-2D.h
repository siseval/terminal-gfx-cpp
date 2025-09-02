#ifndef GFX_PRIMITIVE_STORE_2D_H
#define GFX_PRIMITIVE_STORE_2D_H

#include "gfx-primitive-2D.h"
#include "ellipse-2D.h"

namespace curspp::graphics
{

class GfxPrimitiveStore2D
{

    public:

    inline void add_item(const std::shared_ptr<GfxPrimitive2D> item)
    {
        items.push_back(item);
    }
    inline std::vector<std::shared_ptr<GfxPrimitive2D>>& get_items()
    {
        return items;
    }

    inline void remove_item(const std::shared_ptr<GfxPrimitive2D> item)
    {
        items.erase(std::remove(items.begin(), items.end(), item), items.end());
    }
    inline void clear()
    {
        items.clear();
    }

    private:

    std::vector<std::shared_ptr<GfxPrimitive2D>> items;
};

}

#endif // GFX_PRIMITIVE_STORE_2D_H
