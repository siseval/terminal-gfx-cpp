#include <stack>
#include <gfx/core/scene-graph-2D.h>

namespace gfx::core
{

void SceneGraph2D::add_item(const std::shared_ptr<GfxPrimitive2D> item, const std::shared_ptr<GfxPrimitive2D> parent)
{
    auto new_node { std::make_shared<SceneNode2D>(item) };
    if (nodes.contains(new_node->get_id()))
    {
        return;
    }
    nodes[new_node->get_id()] = new_node;

    if (parent != nullptr && nodes.contains(parent->get_id()))
    {
        auto parent_node { nodes[parent->get_id()] };
        new_node->parent = parent_node;
        parent_node->children.push_back(new_node);
        return;
    }
    new_node->parent = root;
    root->children.push_back(new_node);
} 

void SceneGraph2D::remove_item(const std::shared_ptr<GfxPrimitive2D> item)
{
    if (!nodes.contains(item->get_id()))
    {
        return;
    }

    nodes[item->get_id()]->parent->children.erase(std::remove_if(
        nodes[item->get_id()]->parent->children.begin(), 
        nodes[item->get_id()]->parent->children.end(), 
        [item](const std::shared_ptr<SceneNode2D> node) { return node->get_id() == item->get_id(); }
    ), nodes[item->get_id()]->parent->children.end());

    std::stack<std::shared_ptr<SceneNode2D>> stack;
    stack.push(nodes[item->get_id()]);
    while (!stack.empty())
    {
        auto node { stack.top() };
        stack.pop();

        for (const auto& child : node->children)
        {
            stack.push(child);
        }

        nodes.erase(node->get_id());
    }
}

}
