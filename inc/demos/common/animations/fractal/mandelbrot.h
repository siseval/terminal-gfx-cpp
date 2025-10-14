#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>
#include <demos/common/animations/fractal/fractal.h>

namespace demos::common::animations::fractal
{

class Mandelbrot : public Fractal
{

public:

    int compute(const std::complex<double> c) override
    {
        std::complex<double> z = 0;
        int iterations = 0;
        while (std::abs(z) <= 2.0 && iterations < max_iterations)
        {
            z = z * z + c;
            ++iterations;
        }
        return iterations;
    }
};

}

#endif // MANDELBROT_H

