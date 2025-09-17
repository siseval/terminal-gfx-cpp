#ifndef VEC2_H
#define VEC2_H

#include <cstdint>
#include <cmath>
#include <functional>

namespace gfx::math 
{

template <typename T>
class Vec2 
{

public:

    T x;
    T y;

    static Vec2<T> create(T x, T y) 
    { 
        return Vec2<T>{x, y}; 
    }

    static Vec2<T> create(T value)
    {
        return Vec2<T> { value, value };
    }

    static Vec2<T> zero() 
    { 
        return Vec2<T> { 0, 0 }; 
    }

    static T cross(Vec2<T> a, Vec2<T> b) 
    { 
        return static_cast<T>(a.x * b.y - a.y * b.x); 
    }

    static T dot(Vec2<T> a, Vec2<T> b)
    {
        return static_cast<T>(a.x * b.x + a.y * b.y);
    }

    static double distance(Vec2<T> a, Vec2<T> b) 
    { 
        return (b - a).length();
    }

    double angle() 
    { 
        return std::atan2(y, x);
    }

    Vec2<double> normalize() 
    { 
        return Vec2<double>{ static_cast<T>(x / length()), static_cast<T>(y / length()) }; 
    }

    Vec2<double> normal() 
    { 
        return Vec2<T>{ -y, x }; 
    }

    double length() 
    { 
        return std::sqrt(x * x + y * y); 
    }

    Vec2<int> round() const 
    { 
        return Vec2<int> { static_cast<int>(std::lround(x)), static_cast<int>(std::lround(y)) }; 
    }

    template <typename U>
    Vec2<T> operator+(const Vec2<U> &other) const 
    { 
        return Vec2<T>{ static_cast<T>(x + other.x), static_cast<T>(y + other.y) }; 
    }
    template <typename U>
    Vec2<T> operator-(const Vec2<U> &other) const 
    { 
        return Vec2<T>{ static_cast<T>(x - other.x), static_cast<T>(y - other.y) }; 
    }
    template <typename U>
    Vec2<T> operator*(const Vec2<U> &other) const 
    { 
        return Vec2<T>{ static_cast<T>(x * other.x), static_cast<T>(y * other.y) }; 
    }
    template <typename U>
    Vec2<T> operator/(const Vec2<U> &other) const 
    { 
        return Vec2<T>{ static_cast<T>(x / other.x), static_cast<T>(y / other.y) }; 
    }

    Vec2<T> operator*(const double &factor) const 
    { 
        return Vec2<T>{ static_cast<T>(x * factor), static_cast<T>(y * factor) }; 
    }
    Vec2<T> operator/(const double &factor) const 
    { 
        return Vec2<T>{ static_cast<T>(x / factor), static_cast<T>(y / factor) }; 
    }

    Vec2<T> operator-() const 
    { 
        return Vec2<T>{ static_cast<T>(-x), static_cast<T>(-y) }; 
    }

    template <typename U>
    Vec2<T>& operator+=(const Vec2<U> &other) 
    { 
        x += other.x; y += other.y; return *this; 
    }
    template <typename U>
    Vec2<T>& operator-=(const Vec2<U> &other) 
    { 
        x -= other.x; y -= other.y; return *this; 
    }
    template <typename U>
    Vec2<T>& operator*=(const Vec2<U> &other) 
    { 
        x *= other.x; y *= other.y; return *this; 
    }
    template <typename U>
    Vec2<T>& operator/=(const Vec2<U> &other) 
    { 
        x /= other.x; y /= other.y; return *this; 
    }

    Vec2<T>& operator*=(const double &factor) 
    { 
        x *= factor; y *= factor; return *this; 
    }
    Vec2<T>& operator/=(const double &factor) 
    { 
        x /= factor; y /= factor; return *this; 
    }

    template <typename U>
    Vec2<T> operator%(const Vec2<U> &other) const 
    {
        return Vec2<T>{ static_cast<T>(static_cast<int64_t>(x) % static_cast<int64_t>(other.x)),
                        static_cast<T>(static_cast<int64_t>(y) % static_cast<int64_t>(other.y)) };
    }

    bool operator==(const Vec2<T> &other) const 
    { 
        return x == other.x && y == other.y; 
    }
    bool operator!=(const Vec2<T> &other) const 
    { 
        return x != other.x || y != other.y; 
    }
    void operator=(const Vec2<T> &other) 
    { 
        x = other.x; y = other.y; 
    }

    template <typename U>
    operator Vec2<U>() const 
    { 
        return { static_cast<U>(x), static_cast<U>(y) }; 
    }
};

using Vec2i = Vec2<int>;
using Vec2d = Vec2<double>;
using Vec2f = Vec2<float>;

}

template <typename T>
struct std::hash<gfx::math::Vec2<T>>
{
    size_t operator()(const gfx::math::Vec2<T>& vec) const
    {
        return std::hash<T>()(vec.x) ^ (std::hash<T>()(vec.y) << 1);
    }
};


#endif // VEC2_H
