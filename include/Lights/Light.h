#pragma once

#include "../Constants.h"
#include "./Tuples/Color.h"
#include "./Tuples/Vector.h"

namespace COAL
{
    struct Light
    {
        [[nodiscard]] constexpr Light() : m_intensity(COAL::Color()), m_position(COAL::Point()) {}

        [[nodiscard]] constexpr Light(COAL::Point &position, COAL::Color &intensity) : m_intensity(intensity), m_position(position) {}

        // abstract equality operator
        [[nodiscard]] virtual bool operator==(const Light &rhs) const noexcept = 0;

        // getters
        [[nodiscard]] constexpr const COAL::Color &get_intensity() const noexcept { return m_intensity; }
        [[nodiscard]] constexpr const COAL::Point &get_position() const noexcept { return m_position; }

        // setters
        constexpr Light &set_intensity(const COAL::Color &intensity) noexcept
        {
            this->m_intensity = intensity;
            return *this;
        }
        constexpr Light &set_position(const COAL::Point &position) noexcept
        {
            this->m_position = position;
            return *this;
        }

        COAL::Color m_intensity;
        COAL::Point m_position;
    };
} // namespace COAL
