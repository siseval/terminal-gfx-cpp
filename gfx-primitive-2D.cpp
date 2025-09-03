#include "gfx-primitive-2D.h"

namespace curspp::graphics
{

Matrix3x3d GfxPrimitive2D::get_transform(std::shared_ptr<gfx_context> context) const
{
    Matrix3x3d scale_matrix = Matrix3x3d({
        { scale.x, 0, 0 },
        { 0, scale.y, 0 },
        { 0, 0, 1 }
    });

    double sin_r = std::sin(rotation);
    double cos_r = std::cos(rotation);
    Matrix3x3d rotation_matrix = Matrix3x3d({
        { cos_r, -sin_r, 0 },
        { sin_r, cos_r, 0 },
        { 0, 0, 1 }
    });
    
    Vec2d pos = get_pos() - get_anchor() * get_size();
    Matrix3x3d translation_matrix = Matrix3x3d({
        { 1, 0, pos.x },
        { 0, 1, pos.y },
        { 0, 0, 1 }
    });

    return translation_matrix * rotation_matrix * scale_matrix;
}

Matrix3x3d GfxPrimitive2D::invert_affine(Matrix3x3d m)
{
    double a = m(0, 0), b = m(0, 1), c = m(0, 2);
    double d = m(1, 0), e = m(1, 1), f = m(1, 2);
    double det = a * e - b * d;

    if (det == 0) 
    {
        throw std::runtime_error("Matrix is not invertible");
    }

    double inv_det = 1.0 / det;

    Matrix3x3d inv;
    inv(0, 0) = e * inv_det;
    inv(0, 1) = -b * inv_det;
    inv(0, 2) = (b * f - c * e) * inv_det;
    inv(1, 0) = -d * inv_det;
    inv(1, 1) = a * inv_det;
    inv(1, 2) = (c * d - a * f) * inv_det;
    inv(2, 0) = 0;
    inv(2, 1) = 0;
    inv(2, 2) = 1;

    return inv;
}

void GfxPrimitive2D::set_pos(const coord2D pos) 
{ 
    coord2D delta = pos - get_pos();
    bounds.min += delta;
    bounds.max += delta;
    // coord2D size = bounds.max - bounds.min;
    // bounds.min = pos - anchor; 
    // bounds.max = bounds.min + size;
}

// void GfxPrimitive2D::rasterize_bounds(std::shared_ptr<gfx_context> context) const
// {
//     Matrix3x3d transform = get_transform(context);
//     coord2D bounds_size = apply_transform(get_size(), transform);
//     coord2D position = get_pos();
//     coord2D anchor_point = get_anchor() * bounds_size;
//     coord2D center = (bounds_size / 2);
//
//     write_pixel(context, position, GFX_BOUNDS_COLOR);
//     write_pixel(context, position - anchor_point, GFX_BOUNDS_COLOR);
//     write_pixel(context, position + coord2D{ 0, bounds_size.y } - anchor_point, GFX_BOUNDS_COLOR);
//     write_pixel(context, position + bounds_size - anchor_point, GFX_BOUNDS_COLOR);
//     write_pixel(context, position + coord2D{ bounds_size.x, 0 } - anchor_point, GFX_BOUNDS_COLOR);
// }

void rasterize_line(std::shared_ptr<gfx_context> context, const coord2D start, const coord2D end, double line_thickness, const Color3 color)
{
    coord_type delta_x = std::abs(end.x - start.x);
    int8_t sign_x = start.x < end.x ? 1 : - 1;

    coord_type delta_y = -std::abs(end.y - start.y);
    int8_t sign_y = start.y < end.y ? 1 : - 1;

    coord_type error = delta_x + delta_y;
    coord2D cur_pos = start;

    coord_type line_extent = line_thickness / 2;

    // vec2f normal_vector = curspp::vec2f::normal(curspp::vec2f::normalize(end - start));
    while (true)
    {
        // for (coord_type i = 0; i < line_thickness ; i++)
        // {
        //     vec2f offset = scale_with_viewport(context, (normal_vector * (i - line_extent)));
        //     write_pixel(context, cur_pos + offset, get_color());
        // }
        rasterize_circle(context, cur_pos, line_extent, color);

        coord_type error_doubled = 2 * error;

        if (error_doubled >= delta_y)
        {
            if (cur_pos.x == end.x)
            {
                break;
            }
            error += delta_y;
            cur_pos.x += sign_x;
        }
        if (error_doubled <= delta_x)
        {
            if (cur_pos.y == end.y)
            {
                break;
            }
            error += delta_x;
            cur_pos.y += sign_y;
        }
    }
}

coord2D apply_transform(const Vec2d pos, const Matrix3x3d transform)
{
    Matrix3x1d column_matrix = Matrix3x1d({ 
        { pos.x }, 
        { pos.y }, 
        { 1 }});

    Matrix3x1d transformed = transform * column_matrix;
    return Vec2d { transformed(0, 0), transformed(1, 0), };
}

void rasterize_bounds(std::shared_ptr<gfx_context> context, const bbox_2D bounds)
{
    write_pixel(context, bounds.min, GFX_BOUNDS_COLOR);
    write_pixel(context, { bounds.min.x, bounds.max.y }, GFX_BOUNDS_COLOR);
    write_pixel(context, bounds.max, GFX_BOUNDS_COLOR);
    write_pixel(context, { bounds.max.x, bounds.min.y }, GFX_BOUNDS_COLOR);
}

void rasterize_anchor(std::shared_ptr<gfx_context> context, const coord2D pos)
{
    write_pixel(context, pos, GFX_ANCHOR_COLOR);
    // rasterize_line(context, pos - coord2D{ 5, 0 }, pos + coord2D{ 5, 0 }, 1.0, GFX_ANCHOR_COLOR);
    // rasterize_line(context, pos - coord2D{ 0, 5 }, pos + coord2D{ 0, 5 }, 1.0, GFX_ANCHOR_COLOR);
}

void rasterize_circle(std::shared_ptr<gfx_context> context, const coord2D center, const double radius, const Color3 color)
{
    Vec2d scaled_radius = Vec2d { radius, radius } * context->viewport_scaling;
    coord_type diameter = radius * 2;
    for (coord_type i = 0; i < diameter * diameter; i++)
    {
        coord2D pos = scale_with_viewport(context, { i % diameter - static_cast<coord_type>(radius), i / diameter - static_cast<coord_type>(radius)});
        double sdf = ((pos.x * pos.x) / (scaled_radius.x * scaled_radius.x)) + ((pos.y * pos.y) / (scaled_radius.y * scaled_radius.y)) - 1;

        if (sdf <= radius)
        {
            write_pixel(context, center + pos, color);
        }
    }
}

Vec2d rotate_point(const coord2D point, const double angle)
{
    double s = sin(angle);
    double c = cos(angle);

    double xnew = point.x * c - point.y * s;
    double ynew = point.x * s + point.y * c;

    return { xnew, ynew };
}


}


