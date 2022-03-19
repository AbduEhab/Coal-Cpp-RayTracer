#pragma once

#include "Tuple.h"

namespace COAL
{
    class Color : public Tuple
    {
    public:
        [[nodiscard]] constexpr Color() : Tuple(x, y, z, 0){};

        [[nodiscard]] constexpr Color(double red, double green, double blue)
            : Tuple(red > 255 ? 255 : red, green > 255 ? 255 : green, blue > 255 ? 255 : blue, 0) {}

        [[nodiscard]] constexpr int operator==(const Color &rhs) const noexcept
        {
            return (std::abs(x - rhs.x) <= 0.00001) && (std::abs(y - rhs.y) <= 0.00001) && (std::abs(z - rhs.z) <= 0.00001) && (rhs.w == 0);
        }

        [[nodiscard]] constexpr Color &operator+=(const double rhs) noexcept
        {
            x = x + rhs;
            y = y + rhs;
            z = z + rhs;
            return *this;
        }

        [[nodiscard]] constexpr Color &operator+=(const Color &rhs) noexcept
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Color &operator-=(const double rhs) noexcept
        {
            x = x - rhs;
            y = y - rhs;
            z = z - rhs;
            return *this;
        }

        [[nodiscard]] constexpr Color &operator-=(const Color &rhs) noexcept
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Color &operator*=(float factor) noexcept
        {
            x *= factor;
            y *= factor;
            z *= factor;
            return *this;
        }

        [[nodiscard]] constexpr Color &operator*=(const Color &rhs) noexcept
        {
            x *= rhs.x;
            y *= rhs.y;
            z *= rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Color operator+(const Color &rhs) const noexcept
        {
            return Color(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        [[nodiscard]] constexpr Color operator+(const double rhs) const noexcept
        {
            return Color(x + rhs, y + rhs, z + rhs);
        }

        [[nodiscard]] constexpr Color operator-(const double rhs) const noexcept
        {
            return Color(x - rhs, y - rhs, z - rhs);
        }

        [[nodiscard]] constexpr Color operator-(const Color &rhs) const noexcept
        {
            return Color(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        [[nodiscard]] constexpr Color operator*(const float factor) const noexcept
        {
            return Color(x * factor, y * factor, z * factor);
        }

        [[nodiscard]] constexpr Color operator*(const Color &rhs) const noexcept
        {
            return Color(x * rhs.x, y * rhs.y, z * rhs.z);
        }
    };

    [[nodiscard]] std::ostream &operator<<(std::ostream &os, const Color &dt)
    {
        os << "(" << dt.x << ", " << dt.y << ", " << dt.z << ")";
        return os;
    };

    static constexpr const Color BLACK = Color(0, 0, 0);
    static constexpr const Color DARK_GREY = Color(0.2, 0.2, 0.2);
    static constexpr const Color WHITE = Color(1, 1, 1);
    static constexpr const Color RED = Color(1, 0, 0);
    static constexpr const Color GREEN = Color(0, 1, 0);
    static constexpr const Color BLUE = Color(0, 0, 1);
    static constexpr const Color PURPLE = Color(1, 0, 1);
    static constexpr const Color YELLOW = Color(1, 1, 0);
}