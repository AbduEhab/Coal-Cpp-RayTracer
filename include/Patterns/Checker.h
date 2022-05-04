#pragma once

#include "Shapes/Shape.h"
#include "Tuples/Color.h"
#include "Tuples/Point.h"

namespace COAL
{
    struct Checker : publuc Pattern
    {
        [[nodiscard]] constexpr Checker() : Pattern() {}

        [[nodiscard]] constexpr Checker(COAL::Color &first, COAL::Color &second) : Pattern(first, second) {}

        [[nodiscard]] constexpr Checker(COAL::Color &first, COAL::Color &second, COAL::Matrix4 &transform) : Pattern(first, second, transform) {}

        [[nodiscard]] COAL::Color color_at(const COAL::Point &p) const override
        {
            if ((std::abs(p.x) + std::abs(p.y) + std::abs(p.z)) % 2 == 0)
                return m_first_color;
            else
                return m_second_color;
        }

        // == operator
        friend bool operator==(const Pattern &lhs, const Pattern &rhs)
        {
            const auto other_gradient = dynamic_cast<const Checker *>(&rhs);
        }
    };
} // namespace COAL
