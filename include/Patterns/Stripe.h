#pragma once

#include "Shapes/Shape.h"
#include "Tuples/Color.h"
#include "Tuples/Point.h"

namespace COAL
{
    struct Stripe : public Pattern
    {
        [[nodiscard]] constexpr Stripe() : Pattern() {}

        [[nodiscard]] constexpr Stripe(COAL::Color &first, COAL::Color &second) : Pattern(first, second) {}

        [[nodiscard]] constexpr Stripe(COAL::Color &first, COAL::Color &second, COAL::Matrix4 &transform) : Pattern(first, second, transform) {}

        [[nodiscard]] COAL::Color color_at(const COAL::Point &p) const override
        {
            if (std::floor(p.x) % 2 == 0)
                return m_first_color;
            else
                return m_second_color;
        }

        // == operator
        friend bool operator==(const Pattern &lhs, const Pattern &rhs)
        {
            const auto other_gradient = dynamic_cast<const Stripe *>(&rhs);
        }
    };
} // namespace COAL
