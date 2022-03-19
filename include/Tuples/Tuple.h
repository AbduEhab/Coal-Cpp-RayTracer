#pragma once

#include "Constants.h"

namespace COAL
{

    class Tuple
    {

    public:
        [[nodiscard]] constexpr Tuple() : x(0), y(0), z(0), w(0) {}

        [[nodiscard]] constexpr Tuple(double x, double y, double z, double w) : x(x), y(y), z(z), w(w) {}

        [[nodiscard]] constexpr int operator==(Tuple &tupleToCompare) const noexcept;

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

        double x;
        double y;
        double z;
        double w;
    };
}