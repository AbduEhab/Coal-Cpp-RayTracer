#pragma once

#include "Material.h"
#include "Matrix.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace COAL
{
    class Shape
    {

        [[nodiscard]] constexpr Shape();

        COAL::Material m_material = COAL::Material();
        COAL::Matrix4 m_transform = COAL::IDENTITY;
        COAL::Matrix4 m_inverse_transform = COAL::IDENTITY;
    };
} // namespace COAL
