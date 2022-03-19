#pragma once

#include "Tuple.h"

namespace COAL
{

    class Vector : public Tuple
    {

    public:
        [[nodiscard]] constexpr Vector() : Tuple() {}

        [[nodiscard]] constexpr Vector(double x, double y, double z) : Tuple(x, y, z, 0) {}

        [[nodiscard]] constexpr int operator==(Vector &rhs) const noexcept
        {
            return (std::abs(x - rhs.x) <= 0.00001) && (std::abs(y - rhs.y) <= 0.00001) && (std::abs(z - rhs.z) <= 0.00001) && (rhs.w == 0);
        }

        [[nodiscard]] constexpr Vector operator-() const noexcept
        {
            return Vector(-x, -y, -z);
        }

        [[nodiscard]] constexpr Vector &operator+=(const double rhs) noexcept
        {
            x = x + rhs;
            y = y + rhs;
            z = z + rhs;
            return *this;
        }

        [[nodiscard]] constexpr Vector &operator+=(const Vector &rhs) noexcept
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Vector &operator-=(const double rhs) noexcept
        {
            x = x - rhs;
            y = y - rhs;
            z = z - rhs;
            return *this;
        }

        [[nodiscard]] constexpr Vector &operator-=(const Vector &rhs) noexcept
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        [[nodiscard]] constexpr Vector &operator*=(float factor) noexcept
        {
            x *= factor;
            y *= factor;
            z *= factor;
            return *this;
        }

        [[nodiscard]] constexpr Vector &operator/=(float factor) noexcept
        {
            x /= factor;
            y /= factor;
            z /= factor;
            return *this;
        }

        [[nodiscard]] constexpr Vector operator+(const Vector &rhs) const noexcept
        {
            return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        [[nodiscard]] constexpr Vector operator+(const double rhs) const noexcept
        {
            return Vector(x + rhs, y + rhs, z + rhs);
        }

        [[nodiscard]] constexpr Vector operator-(const double rhs) const noexcept
        {
            return Vector(x - rhs, y - rhs, z - rhs);
        }

        [[nodiscard]] constexpr Vector operator-(const Vector &rhs) const noexcept
        {
            return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        [[nodiscard]] constexpr Vector operator*(const float factor) const noexcept
        {
            return Vector(x * factor, y * factor, z * factor);
        }

        [[nodiscard]] constexpr Vector operator/(const float factor) const noexcept
        {
            return Vector(x / factor, y / factor, z / factor);
        }

        [[nodiscard]] constexpr double magnitude(const Tuple &vector) const noexcept
        {
            return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z +
                             vector.w * vector.w);
        }

        [[nodiscard]] constexpr Vector normalize() const noexcept
        {
            double mag = magnitude(*this);

            return *this / mag;
        }

        [[nodiscard]] constexpr float dot(const Vector &b) const noexcept
        {
            return x * b.x + y * b.y + z * b.z + w * b.w;
        }

        [[nodiscard]] constexpr Vector cross(const Vector &b) const noexcept
        {
            return Vector(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
        }

        [[nodiscard]] constexpr Vector reflect(const Vector &b) noexcept
        { // return subtract(b.multiply(2 * dot(b)))
            return *this - (b * (2 * this->dot(b)));
        }
    };

    [[nodiscard]] std::ostream &operator<<(std::ostream &os, const Vector &dt)
    {
        os << "<" << dt.x << ", " << dt.y << ", " << dt.z << ">";
        return os;
    };
}