#ifndef DEMO_UTILS_H
#define DEMO_UTILS_H

#include <random>
#include <chrono>

namespace demos::common::core::utils
{

inline double ease_in_out_cubic(double t)
{
    return t < 0.5
        ? 4.0 * t * t * t
        : 1.0 - pow(-2.0 * t + 2.0, 3) / 2.0;
}

inline double smoothstep(const double d)
{
    return d * d * (3 - 2 * d);
}

inline double exponential_step(const double t, const double k = 5.0)
{
    return (1.0 - std::exp(-k * t)) / (1.0 - std::exp(-k));
}

inline double exponential_interp_3(const double a, const double b, const double c, const double t, const double k = 5.0)
{
    double exp_t = (1.0 - std::exp(-k * t)) / (1.0 - std::exp(-k));

    double ab = a + (b - a) * exp_t;
    double bc = b + (c - b) * exp_t;

    return ab + (bc - ab) * exp_t;
}

inline double random_double(const double min, const double max)
{
    static std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> dist(min, max);
    return dist(rng);
}

inline int random_int(const int min, const int max)
{
    static std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

inline double time_sec()
{
    return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count()) / 1000.0;
}

inline double time_ms()
{
    return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
}

inline double time_us()
{
    return static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count());
}

inline double lerp(const double a, const double b, const double t)
{
    return a + (b - a) * (t < 0 ? 0 : (t > 1 ? 1 : t));
}

inline double inv_lerp(int a, int b, double v)
{
    return (v - a) / (b - a);
}

}

#endif // DEMO_UTILS_H
