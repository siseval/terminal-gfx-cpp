#include <algorithm>
#include <utility>
#include <stack>
#include <gfx/core/scene-graph-2D.h>
#include <gfx/math/matrix.h>

namespace gfx::core
{

using namespace gfx::math;

void SceneGraph2D::update_global_transforms()
{
    std::stack<std::pair<std::shared_ptr<SceneNode2D>, Matrix3x3d>> stack;

    stack.push({ get_root(), get_root()->global_transform });

    while (!stack.empty())
    {
        auto [node, parent_transform] { stack.top() };
        stack.pop();

        if (node->primitive)
        {
            node->global_transform = parent_transform * node->primitive->get_transform();
        }
        else
        {
            node->global_transform = parent_transform;
        }

        node->cached_transform_version = node->primitive ? 
            node->primitive->get_transform_version() : 
            0;

        for (const auto &child : node->children)
        {
            if (child->primitive == nullptr) 
            {
                stack.push({ child, node->global_transform });
                continue; 
            }
            stack.push({ child, node->global_transform });
        }
    }
}

Matrix3x3d SceneGraph2D::get_global_transform(const std::shared_ptr<Primitive2D> primtive)
{
    auto node { nodes.contains(primtive->get_id()) ? nodes.at(primtive->get_id()) : nullptr };
    if (node == nullptr)
    {
        return Matrix3x3d::identity();
    }
    if (node->primitive == nullptr)
    {
        return node->global_transform;
    }
    uint64_t current_version { node->primitive->get_transform_version() };
    if (current_version != node->cached_transform_version)
    {
        update_global_transforms();
        node->cached_transform_version = current_version;
    }
    return node->global_transform;
}

std::vector<std::pair<std::shared_ptr<Primitive2D>, Matrix3x3d>> SceneGraph2D::get_draw_queue()
{
    std::vector<std::pair<std::shared_ptr<Primitive2D>, Matrix3x3d>> draw_queue;
    for (const auto& [id, node] : nodes)
    {
        if (node->primitive != nullptr)
        {
            draw_queue.push_back({ node->primitive, get_global_transform(node->primitive) });
        }
    }
    std::sort(draw_queue.begin(), draw_queue.end(), [](const auto& a, const auto& b) {
        return a.first->get_depth() > b.first->get_depth();
    });
    return draw_queue;
}

void SceneGraph2D::add_item(const std::shared_ptr<Primitive2D> item, const std::shared_ptr<Primitive2D> parent)
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

void SceneGraph2D::remove_item(const std::shared_ptr<Primitive2D> item)
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
