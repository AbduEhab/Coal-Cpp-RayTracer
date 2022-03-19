#pragma once

#include "../Constants.h"
#include "./Tuples/Color.h"
#include "./Tuples/Vector.h"

namespace COAL
{
    class Light
    {
    public:
        [[nodiscard]] constexpr Light() : intensity(COAL::Color()), position(COAL::Point()) {}

        [[nodiscard]] constexpr Light(COAL::Color &intensity, COAL::Point &position) : intensity(intensity), position(position) {}

        COAL::Color intensity;
        COAL::Point position;
    };
} // namespace COAL
