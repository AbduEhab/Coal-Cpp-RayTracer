#pragma once

#include "../Constants.h"
#include "./Tuples/Color.h"
#include "./Tuples/Vector.h"

namespace COAL
{
    class PointLight : public Light
    {
    public:
        [[nodiscard]] constexpr PointLight() : Light() {}

        [[nodiscard]] constexpr PointLight(COAL::Color &intensity, COAL::Point &position) : Light(intensity, position) {}

        [[nodiscard]] int equals(PointLight &p) const
        {
            return intensity == p.intensity && position == p.position;
        }
    };
} // namespace COAL
