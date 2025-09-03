#ifndef POLYLINE_2D_H
#define POLYLINE_2D_H

#include "gfx-primitive-2D.h"

namespace curspp::graphics
{

class Polyline2D : public GfxPrimitive2D
{

public:

    void rasterize(std::shared_ptr<gfx_context> context) override;
    void update_bounds(std::shared_ptr<gfx_context> context) override;

    inline void add_point(const coord2D point) { points.push_back(point); }
    inline void add_points(const std::vector<coord2D>& new_points) { points.insert(points.end(), new_points.begin(), new_points.end()); }
    inline void set_points(const std::vector<coord2D>& new_points) { points = new_points; }
    inline const std::vector<coord2D>& get_points() const { return points; }
    inline void clear_points() { points.clear(); }


protected:

    std::vector<coord2D> points = std::vector<coord2D>();
};

};

#endif // POLYLINE_2D_H
