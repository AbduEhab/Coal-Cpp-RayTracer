#pragma once

#include "Shapes/Shape.h"
#include "Tuples/Color.h"
#include "Tuples/Point.h"

namespace COAL
{
    struct Gradient : publuc Pattern
    {
        [[nodiscard]] constexpr Gradient() : Pattern() {}

        [[nodiscard]] constexpr Gradient(COAL::Color &first, COAL::Color &second) : Pattern(first, second) {}

        [[nodiscard]] constexpr Gradient(COAL::Color &first, COAL::Color &second, COAL::Matrix4 &transform) : Pattern(first, second, transform) {}

        [[nodiscard]] COAL::Color color_at(const COAL::Point &p) const override
        {
            // float x = p.x;
            // float y = p.y;
            // float z = p.z;

            // float r = (x * m_transform[0][0] + y * m_transform[0][1] + z * m_transform[0][2] + m_transform[0][3]) /
            //            (x * m_transform[3][0] + y * m_transform[3][1] + z * m_transform[3][2] + m_transform[3][3]);
            // float g = (x * m_transform[1][0] + y * m_transform[1][1] + z * m_transform[1][2] + m_transform[1][3]) /
            //            (x * m_transform[3][0] + y * m_transform[3][1] + z * m_transform[3][2] + m_transform[3][3]);
            // float b = (x * m_transform[2][0] + y * m_transform[2][1] + z * m_transform[2][2] + m_transform[2][3]) /
            //            (x * m_transform[3][0] + y * m_transform[3][1] + z * m_transform[3][2] + m_transform[3][3]);

            // return COAL::Color(r, g, b);

            Color distance = m_second_color - m_first_color;
            float fraction = p.x - std::floor(p.x);

            return m_first_color + distance * fraction;
        }

        // == operator
        friend bool operator==(const Pattern &lhs, const Pattern &rhs)
        {
            const auto other_gradient = dynamic_cast<const Gradient *>(&rhs);
        }
    };
} // namespace COAL
