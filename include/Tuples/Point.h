#pragma once

#include "Tuple.h"
#include "Vector.h"

namespace COAL
{
    class Point : public Tuple
    {
    public:
        [[nodiscard]] constexpr Point() : Tuple(0, 0, 0, 1){};

        [[nodiscard]] constexpr Point(double x, double y, double z) : Tuple(x, y, z, 1) {}

        [[nodiscard]] constexpr int operator==(Point &rhs) const noexcept
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

        [[nodiscard]] constexpr Vector operator-(const Point &rhs) const noexcept
        {
            return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
        }
    };

    [[nodiscard]] std::ostream &operator<<(std::ostream &os, const Point &dt)
    {
        os << "(" << dt.x << ", " << dt.y << ", " << dt.z << ")";
        return os;
    };
}