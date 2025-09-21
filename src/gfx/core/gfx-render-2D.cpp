#include <algorithm>
#include <stack>
#include <gfx/core/gfx-render-2D.h>

namespace gfx::core
{

using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;


void GfxRender2D::draw_frame() const
{
    surface->clear_frame_buffer();

    std::vector<std::pair<std::shared_ptr<GfxPrimitive2D>, Matrix3x3d>> draw_queue = get_draw_queue();
    for (auto& [primitive, transform] : draw_queue)
    {
        primitive->rasterize(surface, transform);

        if (primitive->get_draw_aabb())
        {
            Box2d bounds = primitive->get_axis_aligned_bounding_box(transform);
            utils::rasterize_aabb(surface, bounds, GFX_BOUNDS_COLOR);
        }
        if (primitive->get_draw_obb())
        {
            OBB2D obb = primitive->get_oriented_bounding_box(transform);
            utils::rasterize_obb(surface, obb, GFX_BOUNDS_COLOR);
        }
        if (primitive->get_draw_anchor())
        {
            Vec2d anchor_pos = utils::transform_point(primitive->get_pos(), get_global_transform());
            utils::rasterize_cross(surface, anchor_pos, 1.0, GFX_ANCHOR_COLOR);
        }
    }

    surface->present();
}

std::vector<std::pair<std::shared_ptr<GfxPrimitive2D>, Matrix3x3d>> GfxRender2D::get_draw_queue() const
{
    std::stack<std::pair<std::shared_ptr<SceneNode2D>, Matrix3x3d>> stack;
    std::vector<std::pair<std::shared_ptr<GfxPrimitive2D>, Matrix3x3d>> draw_queue;

    stack.push({ scene_graph->get_root(), get_global_transform() });

    while (!stack.empty())
    {
        auto [node, parent_transform] = stack.top();
        stack.pop();

        if (node->primitive)
        {
            draw_queue.push_back({ node->primitive, parent_transform });
        }

        for (const auto& child : node->children)
        {
            if (child->primitive == nullptr) 
            {
                stack.push({ child, parent_transform });
                continue; 
            }
            stack.push({ child, parent_transform * child->primitive->get_transform() });
        }
    }
    std::sort(draw_queue.begin(), draw_queue.end(), [](const auto& a, const auto& b) {
        return a.first->get_depth() > b.first->get_depth();
    });

    return draw_queue;
}

gfx::math::Matrix3x3d GfxRender2D::get_global_transform() const
{
    Matrix3x3d scale = utils::scale(viewport_scaling);
    return scale;
}

std::shared_ptr<Ellipse2D> GfxRender2D::create_ellipse(const Vec2d position, const Vec2d radius, const Color4 color, const double line_thickness) const
{
    auto ellipse = std::make_shared<Ellipse2D>();

    ellipse->set_pos(position);
    ellipse->set_radius(radius);
    ellipse->set_line_thickness(line_thickness);
    ellipse->set_color(color);

    return ellipse;
}

std::shared_ptr<Polyline2D> GfxRender2D::create_polyline(const Vec2d position, const std::vector<Vec2d> points, const Color4 color, const double line_thickness) const
{
    auto polyline = std::make_shared<Polyline2D>();

    polyline->set_pos(position);
    polyline->set_points(points);
    polyline->set_line_thickness(line_thickness);
    polyline->set_color(color);

    return polyline;
}

}
