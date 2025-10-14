#include <gfx/geometry/triangulate.h>
#include <gfx/math/box2.h>

namespace gfx::geometry
{

using namespace gfx::math;


bool is_convex(const Triangle &triangle, const bool clockwise)
{
    Vec2d ab { triangle.v1 - triangle.v0 };
    Vec2d ac { triangle.v2 - triangle.v0 };
    double cross { ab.x * ac.y - ab.y * ac.x };
    return clockwise ? cross > 0 : cross < 0;
}

bool is_ear(const int index, const std::vector<int> &indices, const std::vector<Vec2d> &vertices, const Triangle &triangle, const int i0, const int i1, const int i2, const bool clockwise)
{
    if (!is_convex(triangle, clockwise))
    {
        return false;
    }

    for (int i = 0 ; i < indices.size(); ++i)
    {
        if (i == i0 || i == i1 || i == i2)
        {
            continue;
        }

        Box2d bounds { triangle.v0, triangle.v0 };
        for (auto v : { triangle.v1, triangle.v2 })
        {
            bounds.expand(v);
        }
        Vec2d point { vertices[indices[i]] };
        if (!bounds.contains(point))
        {
            continue;
        }

        if (triangle.point_inside(point))
        {
            return false;
        }
    }
    return true;
}

std::vector<Triangle> triangulate_polygon(const std::vector<Vec2d> &vertices, const bool clockwise)
{
    std::vector<Triangle> triangles;
    if (vertices.size() < 3)
    {
        return triangles;
    }

    std::vector<int> indices;
    indices.reserve(vertices.size());
    for (int i = 0; i < vertices.size(); ++i)
    {
        indices.push_back(i);
    }

    while (indices.size() > 3)
    {
        bool ear_found = false;
        for (int i = 0; i < indices.size(); ++i)
        {
            int prev_index { indices[(i == 0) ? indices.size() - 1 : i - 1] };
            int cur_index { indices[i] };
            int next_index { indices[(i + 1) >= indices.size() ? 0 : i + 1] };

            Triangle candidate { vertices[prev_index], vertices[cur_index], vertices[next_index] };

            if (is_ear(i, indices, vertices, candidate, prev_index, cur_index, next_index, clockwise))
            {
                triangles.push_back(candidate);
                indices.erase(indices.begin() + i);
                ear_found = true;
                break;
            }
        }
        if (!ear_found)
        {
            triangles.clear();
            return triangles;
        }
    }
    triangles.emplace_back(vertices[indices[0]], vertices[indices[1]], vertices[indices[2]]);

    return triangles;
}

}
