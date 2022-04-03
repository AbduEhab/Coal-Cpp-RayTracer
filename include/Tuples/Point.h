#pragma once

#include "Vector.h"

namespace COAL
{
    class Point
    {
    public:
        [[nodiscard]] constexpr Point() : x(0), y(0), z(0), w(1){};

        [[nodiscard]] constexpr Point(double x, double y, double z) : x(x), y(y), z(z), w(0){};

        [[nodiscard]] int operator==(Point &rhs) const noexcept
        {
            return (std::abs(x - rhs.x) <= 0.00001) && (std::abs(y - rhs.y) <= 0.00001) && (std::abs(z - rhs.z) <= 0.00001) && (rhs.w == 1);
        }

        [[nodiscard]] constexpr Point &operator+=(const double rhs) noexcept
        {
            x = x + rhs;
            y = x + rhs;
            z = x + rhs;
            w = w + rhs;
            return *this;
        }

        [[nodiscard]] constexpr Point &operator+=(const Point &rhs) noexcept
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Point &operator-=(const double rhs) noexcept
        {
            x = x - rhs;
            y = y - rhs;
            z = z - rhs;
            return *this;
        }

        [[nodiscard]] Vector operator-(const Point &rhs) const noexcept
        {
            return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        friend std::ostream &operator<<(std::ostream &os, const Point &dt)
        {
            os << "(" << dt.x << ", " << dt.y << ", " << dt.z << ")";
            return os;
        };

        double x;
        double y;
        double z;
        double w;
    };

}