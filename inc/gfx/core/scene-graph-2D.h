#ifndef GFX_PRIMITIVE_STORE_2D_H
#define GFX_PRIMITIVE_STORE_2D_H

#include <gfx/core/gfx-primitive-2D.h>
#include <gfx/utils/uuid.h>

namespace gfx::core
{

struct SceneNode2D
{
    SceneNode2D(std::shared_ptr<GfxPrimitive2D> item) : primitive(item) {}

    utils::UUID get_id() const
    {
        if (primitive)
        {
            return primitive->get_id();
        }
        return utils::UUID(0, 0);
    }
    std::shared_ptr<GfxPrimitive2D> primitive;
    std::shared_ptr<SceneNode2D> parent = nullptr;
    std::vector<std::shared_ptr<SceneNode2D>> children;
};

class SceneGraph2D
{

public:

    SceneGraph2D() : 
        root(std::make_shared<SceneNode2D>(nullptr)),
        nodes(std::unordered_map<gfx::utils::UUID, std::shared_ptr<SceneNode2D>>()) {}

    inline std::shared_ptr<SceneNode2D> get_root() const { return root; }

    void add_item(const std::shared_ptr<GfxPrimitive2D> item, const std::shared_ptr<GfxPrimitive2D> parent);

    inline void add_item(const std::shared_ptr<GfxPrimitive2D> item)
    {
        add_item(item, nullptr);
    }

    void remove_item(const std::shared_ptr<GfxPrimitive2D> item);

    inline void clear()
    {
        root->children.clear();
        nodes.clear();
    }

    inline int num_items() const { return item_count; }
    inline bool contains_item(const std::shared_ptr<GfxPrimitive2D> item) const { return nodes.contains(item->get_id()); }

private:
    std::shared_ptr<SceneNode2D> root;
    std::unordered_map<gfx::utils::UUID, std::shared_ptr<SceneNode2D>> nodes;
    int item_count = 0;

};

}

#endif // GFX_PRIMITIVE_STORE_2D_H
