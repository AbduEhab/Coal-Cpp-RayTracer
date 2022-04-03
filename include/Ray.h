#pragma once

#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace COAL
{
    class Ray
    {

        [[nodiscard]] constexpr Ray(const Point &origin, const Vector &direction)
            : m_origin(origin), m_direction(direction)
        {
        }

        

    private:
        COAL::Point m_origin;
        COAL::Vector m_direction;
    };
} // namespace COAL
