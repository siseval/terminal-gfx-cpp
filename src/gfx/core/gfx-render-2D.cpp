#include <algorithm>
#include <stack>
#include <gfx/core/gfx-render-2D.h>
#include <gfx/utils/transform.h>

namespace gfx::core
{

using namespace gfx::core::types;
using namespace gfx::primitives;
using namespace gfx::math;


void GfxRender2D::draw_frame() const
{
    surface->clear_frame_buffer();

    std::vector<std::pair<std::shared_ptr<GfxPrimitive2D>, Matrix3x3d>> draw_queue { get_draw_queue() };
    for (const auto& [primitive, transform] : draw_queue)
    {
        if (!primitive->is_visible())
        {
            continue;
        }
        primitive->rasterize(surface, transform);
    }

    surface->clear();
    surface->present();
}

std::vector<std::pair<std::shared_ptr<GfxPrimitive2D>, Matrix3x3d>> GfxRender2D::get_draw_queue() const
{
    std::stack<std::pair<std::shared_ptr<SceneNode2D>, Matrix3x3d>> stack;
    std::vector<std::pair<std::shared_ptr<GfxPrimitive2D>, Matrix3x3d>> draw_queue;

    stack.push({ scene_graph->get_root(), get_global_transform() });

    while (!stack.empty())
    {
        auto [node, parent_transform] { stack.top() };
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
    Matrix3x3d scale { utils::scale(viewport_scaling) };
    return scale;
}

std::shared_ptr<Circle2D> GfxRender2D::create_circle(const Vec2d position, const double radius, const Color4 color, const double line_thickness) const
{
    auto circle { std::make_shared<Circle2D>() };

    circle->set_position(position);
    circle->set_radius(radius);
    circle->set_line_thickness(line_thickness);
    circle->set_color(color);

    return circle;
}

std::shared_ptr<Ellipse2D> GfxRender2D::create_ellipse(const Vec2d position, const Vec2d radius, const Color4 color, const double line_thickness) const
{
    auto ellipse { std::make_shared<Ellipse2D>() };

    ellipse->set_position(position);
    ellipse->set_radius(radius);
    ellipse->set_line_thickness(line_thickness);
    ellipse->set_color(color);

    return ellipse;
}

std::shared_ptr<Polyline2D> GfxRender2D::create_polyline(const Vec2d position, const std::vector<Vec2d> &points, const Color4 color, const double line_thickness) const
{
    auto polyline { std::make_shared<Polyline2D>() };

    polyline->set_position(position);
    polyline->set_points(points);
    polyline->set_line_thickness(line_thickness);
    polyline->set_color(color);

    return polyline;
}

std::shared_ptr<Bitmap2D> GfxRender2D::create_bitmap(const Vec2d position, const gfx::core::types::Bitmap &bm) const
{
    auto bitmap { std::make_shared<Bitmap2D>() };

    bitmap->set_position(position);
    bitmap->load_bitmap(bm);

    return bitmap;
}

std::shared_ptr<Bitmap2D> GfxRender2D::create_bitmap(const Vec2d position, const Vec2i resolution) const
{
    auto bitmap { std::make_shared<Bitmap2D>() };

    bitmap->set_position(position);
    bitmap->set_resolution(resolution);

    return bitmap;
}

}
