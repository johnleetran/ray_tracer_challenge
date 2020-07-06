#include <cmath>
#include <iostream>

#pragma once

namespace Ray_Tracer{
namespace Tuple3D{
    //my 3d tuples
    template <typename T>
    class Tuple3D {
    public:
        T x;
        T y;
        T z;
        T w;
        Tuple3D(T x, T y, T z, T w):x(x),y(y),z(z),w(w){}
        T magnitude()
        {
            T new_x = x * x;
            T new_y = y * y;
            T new_z = z * z;
            T new_w = w * w;

            T mag = std::sqrt(new_x + new_y + new_z + new_w);
            return mag;
        }

        Tuple3D<T> normalize()
        {
            Tuple3D<T> t1{x,y,z,w};
            T new_x = x / magnitude();
            T new_y = y / magnitude();
            T new_z = z / magnitude();
            T new_w = w / magnitude();

            Tuple3D<T> normalized = {new_x, new_y, new_z, new_w};
            return normalized;
        }

        T dot(Tuple3D<T> t1, Tuple3D<T> t2)
        {
            T x = t1.x * t2.x;
            T y = t1.y * t2.y;
            T z = t1.z * t2.z;
            T w = t1.w * t2.w;

            T dot = x + y + z + w;
            return dot;
        }
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &output, const Tuple3D<T> &t1)
    {
        output << "x: " << t1.x << " y: " << t1.y << " z: " << t1.z << " w: " << t1.w << std::endl;
        return output;
    }

    template <typename T>
    Tuple3D<T> operator+(const Tuple3D<T> &t1, const Tuple3D<T> &t2)
    {
        T new_x = t1.x + t2.x;
        T new_y = t1.y + t2.y;
        T new_z = t1.z + t2.z;
        T new_w = t1.w + t2.w;

        Tuple3D<T> sum{new_x, new_y, new_z, new_w};
        return sum;
    }

    template <typename T>
    Tuple3D<T> operator-(const Tuple3D<T> &t1, const Tuple3D<T> &t2)
    {
        T new_x = t1.x - t2.x;
        T new_y = t1.y - t2.y;
        T new_z = t1.z - t2.z;
        T new_w = t1.w - t2.w;

        Tuple3D<T> diff = {new_x, new_y, new_z, new_w};
        return diff;
    }

    template <typename T>
    Tuple3D<T> operator-(const Tuple3D<T> &t1)
    {
        Tuple3D<T> zero = {0, 0, 0, 0};
        Tuple3D<T> neg = zero - t1;
        return neg;
    }

    template <typename T>
    Tuple3D<T> operator*(const Tuple3D<T> &t1, const T &multiplier)
    {
        T new_x = t1.x * multiplier;
        T new_y = t1.y * multiplier;
        T new_z = t1.z * multiplier;
        T new_w = t1.w * multiplier;

        Tuple3D<T> product = {new_x, new_y, new_z, new_w};
        return product;
    }

    template <typename T>
    Tuple3D<T> operator/(const Tuple3D<T> &t1, const T &divisor)
    {
        T new_x = t1.x / divisor;
        T new_y = t1.y / divisor;
        T new_z = t1.z / divisor;
        T new_w = t1.w / divisor;

        Tuple3D<T> div = {new_x, new_y, new_z, new_w};
        return div;
    }
}
} // namespace Ray_Tracer
