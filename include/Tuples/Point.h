#pragma once

#include "Vector.h"

namespace COAL
{
    struct Point
    {
        [[nodiscard]] constexpr Point() : x(0), y(0), z(0), w(1){};

        [[nodiscard]] constexpr Point(double x, double y, double z) : x(x), y(y), z(z), w(1){};

        [[nodiscard]] bool operator==(const Point &rhs) const noexcept
        {
            return (std::abs(x - rhs.x) <= kEpsilon) && (std::abs(y - rhs.y) <= kEpsilon) && (std::abs(z - rhs.z) <= kEpsilon) && (rhs.w == 1);
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

        // - point
        [[nodiscard]] constexpr Point operator-() const noexcept
        {
            return Point(-x, -y, -z);
        }

        // subtract a point from a point
        [[nodiscard]] constexpr Vector operator-(const Point &rhs) const noexcept
        {
            return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        // subtract a vector from a point
        [[nodiscard]] constexpr Point operator-(const Vector &rhs) const noexcept
        {
            return Point(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        // add a point to a Vector
        [[nodiscard]] constexpr Point operator+(const Vector &rhs) const noexcept
        {
            return Point(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        // [] operator
        [[nodiscard]] constexpr double operator[](const char i) const noexcept
        {
            assert(i >= 0 && i < 3);

            switch (i)
            {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                break;
            }

            assert(false);
            return -1;
        }

        [[nodiscard]] constexpr Point &operator*=(const double rhs) noexcept
        {
            x = x * rhs;
            y = y * rhs;
            z = z * rhs;
            return *this;
        }

        [[nodiscard]] constexpr Point &operator/=(const double rhs) noexcept
        {
            x = x / rhs;
            y = y / rhs;
            z = z / rhs;
            return *this;
        }

        [[nodiscard]] constexpr Point &operator*=(const Point &rhs) noexcept
        {
            x = x * rhs.x;
            y = y * rhs.y;
            z = z * rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Point &operator/=(const Point &rhs) noexcept
        {
            x = x / rhs.x;
            y = y / rhs.y;
            z = z / rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Point &operator*=(const Vector &rhs) noexcept
        {
            x = x * rhs.x;
            y = y * rhs.y;
            z = z * rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Point &operator/=(const Vector &rhs) noexcept
        {
            x = x / rhs.x;
            y = y / rhs.y;
            z = z / rhs.z;
            return *this;
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