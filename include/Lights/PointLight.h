#pragma once

#include "../Constants.h"
#include "./Tuples/Color.h"
#include "./Tuples/Vector.h"

namespace COAL
{
    struct PointLight : public Light
    {
        [[nodiscard]] constexpr PointLight() : Light() {}

        [[nodiscard]] constexpr PointLight(COAL::Point &position, COAL::Color &intensity) : Light(position, intensity) {}

        // implement abstract equality
        [[nodiscard]] bool operator==(const Light &rhs) const noexcept override
        {
            const auto other_point_light = dynamic_cast<const PointLight *>(&rhs);
            return other_point_light != nullptr && other_point_light->get_position() == get_position() && other_point_light->get_intensity() == get_intensity();
        };

        // get name
        [[nodiscard]] const char *get_name() const override
        {
            return "PointLight ";
        }
    };
} // namespace COAL
