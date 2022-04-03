#pragma once

#include "Shapes/Shape.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace COAL
{
    class Intersection
    {

        [[nodiscard]] constexpr Intersection()
            : m_t(0)
        {
        }

    private:
        double m_t;
        COAL::Shape m_object;
    };
} // namespace COAL
