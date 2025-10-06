#ifndef TTF_PARSER_H
#define TTF_PARSER_H

#include <gfx/fonts/font-manager.h>
#include <gfx/fonts/font-ttf.h>

namespace gfx::fonts
{

class FontManagerTTF
{

public:

    std::shared_ptr<FontTTF> load_from_file(const std::string &path);
    std::shared_ptr<FontTTF> load_from_memory(const uint8_t* data, const std::size_t size);

private:

    std::unordered_map<uint32_t, uint16_t> parse_cmap_format_4(const std::uint8_t* cmap_table, const uint32_t length);
    std::vector<uint16_t> parse_loca_table(const std::uint8_t* loca_table, const uint16_t num_glyphs, uint16_t index_to_loc_format);
    std::shared_ptr<GlyphTTF> parse_glyph(const std::uint8_t* glyf_table, const std::vector<uint16_t> &glyph_offsets, const uint16_t glyph_index, bool loca_long_format);

};

}

#endif // TTF_PARSER_H
