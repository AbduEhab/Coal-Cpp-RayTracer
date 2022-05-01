#pragma once

#include "../Constants.h"
#include "./Tuples/Color.h"
#include "./Tuples/Vector.h"

namespace COAL
{
    struct Light
    {
        [[nodiscard]] constexpr Light() : intensity(COAL::Color()), position(COAL::Point()) {}

        [[nodiscard]] constexpr Light(COAL::Point &position, COAL::Color &intensity) : intensity(intensity), position(position) {}

        // abstract equality operator
        [[nodiscard]] virtual bool operator==(const Light &rhs) const noexcept = 0;

        // getters
        [[nodiscard]] constexpr const COAL::Color &get_intensity() const noexcept { return intensity; }
        [[nodiscard]] constexpr const COAL::Point &get_position() const noexcept { return position; }

        // setters
        constexpr Light &set_intensity(const COAL::Color &intensity) noexcept
        {
            this->intensity = intensity;
            return *this;
        }
        constexpr Light &set_position(const COAL::Point &position) noexcept
        {
            this->position = position;
            return *this;
        }

        COAL::Color intensity;
        COAL::Point position;
    };
} // namespace COAL
