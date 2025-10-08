#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include <memory.h>
#include <gfx/text/font.h>

namespace gfx::text
{

class FontManager
{

public:

    virtual std::shared_ptr<Font> load_from_file(const std::string &path) = 0;
    virtual std::shared_ptr<Font> load_from_memory(const std::vector<std::byte> &data, const std::size_t size) = 0;
};

}

#endif // FONT_MANAGER_H
