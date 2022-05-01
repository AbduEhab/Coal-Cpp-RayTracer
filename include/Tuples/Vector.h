#pragma once

namespace COAL
{

    struct Vector
    {

        [[nodiscard]] constexpr Vector() : x(0), y(0), z(0), w(0){};

        [[nodiscard]] constexpr Vector(double x, double y, double z) : x(x), y(y), z(z), w(0){};

        [[nodiscard]] int operator==(const Vector &rhs) const noexcept
        {
            return (std::abs(x - rhs.x) <= kEpsilon) && (std::abs(y - rhs.y) <= kEpsilon) && (std::abs(z - rhs.z) <= kEpsilon) && (rhs.w == 0);
        }

        [[nodiscard]] Vector operator-() const noexcept
        {
            return Vector(-x, -y, -z);
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

        [[nodiscard]] constexpr Vector &operator*=(double factor) noexcept
        {
            x *= factor;
            y *= factor;
            z *= factor;
            return *this;
        }

        [[nodiscard]] constexpr Vector &operator/=(double factor) noexcept
        {
            x /= factor;
            y /= factor;
            z /= factor;
            return *this;
        }

        [[nodiscard]] Vector operator+(const Vector &rhs) const noexcept
        {
            return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        [[nodiscard]] Vector operator+(const double rhs) const noexcept
        {
            return Vector(x + rhs, y + rhs, z + rhs);
        }

        [[nodiscard]] Vector operator-(const double rhs) const noexcept
        {
            return Vector(x - rhs, y - rhs, z - rhs);
        }

        [[nodiscard]] Vector operator-(const Vector &rhs) const noexcept
        {
            return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        [[nodiscard]] Vector operator*(const double factor) const noexcept
        {
            return Vector(x * factor, y * factor, z * factor);
        }

        [[nodiscard]] Vector operator/(const double factor) const noexcept
        {
            return Vector(x / factor, y / factor, z / factor);
        }

        friend std::ostream &operator<<(std::ostream &os, const Vector &vector)
        {
            os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
            return os;
        }

        [[nodiscard]] double magnitude() const noexcept
        {
            return std::sqrt(x * x + y * y + z * z +
                             w * w);
        }

        [[nodiscard]] Vector normalize() const noexcept
        {
            double mag = magnitude();

            return *this / (float)mag;
        }

        [[nodiscard]] constexpr double dot(const Vector &b) const noexcept
        {
            return x * b.x + y * b.y + z * b.z + w * b.w;
        }

        [[nodiscard]] Vector cross(const Vector &b) const noexcept
        {
            return Vector(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
        }

        // reflection
        [[nodiscard]] Vector reflect(const Vector &b) const noexcept
        {
            return Vector(x - 2 * b.x, y - 2 * b.y, z - 2 * b.z);
        }

        // [[nodiscard]] constexpr Vector reflect(const Vector &b) noexcept
        // { // return subtract(b.multiply(2 * dot(b)))
        //     return *this - (b * (2 * this->dot(b)));
        // }

        double x;
        double y;
        double z;
        double w;
    };
}