#ifndef FRACTAL_H
#define FRACTAL_H

#include <complex>
#include <gfx/math/vec2.h>

namespace demos::common::animations::fractal
{

class Fractal
{

public:

    virtual int compute(const std::complex<double> c) = 0;

    inline void set_max_iterations(const int it) { max_iterations = it; }
    inline int get_max_iterations() const { return max_iterations; }

protected:

    int max_iterations { 50 };

};

}

#endif // FRACTAL_H
