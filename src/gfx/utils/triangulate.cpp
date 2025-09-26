#include <gfx/utils/triangulate.h>

namespace gfx::utils
{

using namespace gfx::math;

bool is_convex(const Triangle &triangle, const bool clockwise)
{
    Vec2d ab = triangle.v1 - triangle.v0;
    Vec2d ac = triangle.v2 - triangle.v0;
    double cross = ab.x * ac.y - ab.y * ac.x;
    return clockwise ? cross > 0 : cross < 0;
}

bool is_ear(const int index, const std::vector<int> &indices, const std::vector<Vec2d> &vertices, const bool clockwise)
{
    int prev_index = indices[(index - 1 + indices.size()) % indices.size()];
    int curr_index = indices[index];
    int next_index = indices[(index + 1) % indices.size()];

    Triangle candidate = { vertices[prev_index], vertices[curr_index], vertices[next_index] };
    if (!is_convex(candidate, clockwise))
    {
        return false;
    }

    for (int i = 0; i < indices.size(); i++)
    {
        if (i == prev_index || i == curr_index || i == next_index)
        {
            continue;
        }
        if (candidate.point_inside(vertices[indices[i]]))
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

    std::vector<int> indices(vertices.size());
    for (int i = 0; i < vertices.size(); i++)
    {
        indices[i] = i;
    }

    while (indices.size() > 3)
    {
        bool ear_found = false;
        for (int i = 0; i < indices.size(); i++)
        {
            if (is_ear(i, indices, vertices, clockwise))
            {
                int prev_index = indices[(i - 1 + indices.size()) % indices.size()];
                int curr_index = indices[i];
                int next_index = indices[(i + 1) % indices.size()];

                triangles.push_back({ vertices[prev_index], vertices[curr_index], vertices[next_index] });
                indices.erase(indices.begin() + i);
                ear_found = true;
                break;
            }
        }
        if (!ear_found)
        {
            return std::vector<Triangle>();
        }
    }
    triangles.push_back({ vertices[indices[0]], vertices[indices[1]], vertices[indices[2]] });

    return triangles;

}

}
