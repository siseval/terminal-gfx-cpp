#ifndef GFX_PRIMITIVE_STORE_2D_H
#define GFX_PRIMITIVE_STORE_2D_H

#include <algorithm>
#include "gfx-primitive-2D.h"
#include "ellipse-2D.h"

namespace curspp::gfx
{

struct compare_primitive_by_depth
{
    bool operator()(const std::shared_ptr<GfxPrimitive2D>& a, const std::shared_ptr<GfxPrimitive2D>& b) const
    {
        return a->get_depth() > b->get_depth();
    }
};

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
        items.erase(std::remove(items.begin(), items.end(), item));
    }
    inline void clear()
    {
        items.clear();
    }

    inline void sort_by_depth()
    {
        std::stable_sort(items.begin(), items.end(), compare_primitive_by_depth());
    }

    inline int num_items() const
    {
        return items.size();
    }

    private:

    std::vector<std::shared_ptr<GfxPrimitive2D>> items = std::vector<std::shared_ptr<GfxPrimitive2D>>();
};

}

#endif // GFX_PRIMITIVE_STORE_2D_H
