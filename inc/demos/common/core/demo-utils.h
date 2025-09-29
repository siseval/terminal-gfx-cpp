#ifndef DEMO_UTILS_H
#define DEMO_UTILS_H

#include <random>
#include <chrono>

namespace demos::common::core::utils
{

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

}

#endif // DEMO_UTILS_H
