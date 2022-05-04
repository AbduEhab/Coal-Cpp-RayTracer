#pragma once

#include "Shapes/Shape.h"
#include "Tuples/Color.h"
#include "Tuples/Point.h"

namespace COAL
{
    struct Ring : publuc Pattern
    {
        [[nodiscard]] constexpr Ring() : Pattern() {}

        [[nodiscard]] constexpr Ring(COAL::Color &first, COAL::Color &second) : Pattern(first, second) {}

        [[nodiscard]] constexpr Ring(COAL::Color &first, COAL::Color &second, COAL::Matrix4 &transform) : Pattern(first, second, transform) {}

        [[nodiscard]] COAL::Color color_at(const COAL::Point &p) const override
        {
            if ((int)(sqrt(p.x * p.x + p.z * p.z)) % 2 == 0)
                return m_first_color;
            else
                return m_second_color;
        }

        // == operator
        friend bool operator==(const Pattern &lhs, const Pattern &rhs)
        {
            const auto other_gradient = dynamic_cast<const Ring *>(&rhs);
        }
    };
} // namespace COAL
