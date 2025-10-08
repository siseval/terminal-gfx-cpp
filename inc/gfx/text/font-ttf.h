#ifndef FONT_TTF_H
#define FONT_TTF_H

#include <vector>
#include <unordered_map>
#include <gfx/text/font.h>
#include <gfx/math/box2.h>

namespace gfx::text
{

struct Point
{
    double x;
    double y;
    bool on_curve;
};

struct GlyphTTF
{
    gfx::math::Box2d bbox;
    std::vector<std::vector<Point>> contours;
};

class FontTTF
{

public:

    FontTTF(int units_per_em, double ascent, double descent, double line_gap, int num_glyphs)
        : units_per_em(units_per_em), ascent(ascent), descent(descent), line_gap(line_gap), num_glyphs(num_glyphs) {}

    std::shared_ptr<GlyphTTF> get_glyph(const char character) const 
    {
        return glyphs.count(static_cast<uint32_t>(character)) ? glyphs.at(static_cast<uint32_t>(character)) : nullptr;
    };
    gfx::math::Vec2d get_kerning(const char left, const char right) const;

    void set_glyphs(const std::unordered_map<uint32_t, std::shared_ptr<GlyphTTF>> &g) { glyphs = g; }
    std::unordered_map<uint32_t, std::shared_ptr<GlyphTTF>> get_glyphs() const { return glyphs; }

private:

    int units_per_em;
    double ascent;
    double descent;
    double line_gap;
    int num_glyphs;

    std::unordered_map<uint32_t, std::shared_ptr<GlyphTTF>> glyphs;
};

}

#endif // FONT_TTF_H
