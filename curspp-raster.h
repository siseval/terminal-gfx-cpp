#ifndef CURSPP_RASTER_H
#define CURSPP_RASTER_H

#include "curspp.h"

namespace curspp
{

struct raster
{
    vec2c dimensions;
    std::shared_ptr<uint8_t> pixels;
};


}

#endif // CURSPP_RASTER_H
