#pragma once

#include "Patterns/Pattern.h"
#include "Tuples/Color.h"

namespace COAL
{
    class Material
    {
    public:
        [[nodiscard]] constexpr Material()
        {
        }

        [[nodiscard]] constexpr Material(COAL::Color &color, double ambient, double diffuse, double specular, double shininess, COAL::Pattern &pattern, double reflectiveness, double transparency, double refractiveIndex)
        {
            if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255)
            {
                std::cout << "invalid color recived " << __FUNCTION__ << std::endl;
            }
            else
            {
                m_color = color;
            }

            if (ambient >= 0 && ambient <= 1)
            {
                this->m_ambient = ambient;
            }
            else
            {
                std::cout << "invalid ambient recived " << __FUNCTION__ << std::endl;
            }

            if (diffuse >= 0 && diffuse <= 1)
            {
                this->m_diffuse = diffuse;
            }
            else
            {
                std::cout << "invalid diffuse recived " << __FUNCTION__ << std::endl;
            }

            if (specular >= 0 && specular <= 1)
            {
                this->m_specular = specular;
            }
            else
            {
                std::cout << "invalid specular recived " << __FUNCTION__ << std::endl;
            }

            if (shininess >= 0 && shininess <= 1)
            {
                this->m_shininess = shininess;
            }
            else
            {
                std::cout << "invalid shininess recived " << __FUNCTION__ << std::endl;
            }

            m_pattern = pattern;

            m_reflectiveness = reflectiveness > 1 ? 1 : reflectiveness < 0 ? 0
                                                                           : reflectiveness;

            m_transparency = transparency >= 0 ? transparency : 0;

            m_refractive_index = refractiveIndex >= 0 ? refractiveIndex : 0;
        }

        // << operator
        friend std::ostream &operator<<(std::ostream &os, const Material &m)
        {
            os << "material: " << std::endl;
            os << "ambient: " << m.m_ambient << std::endl;
            os << "diffuse: " << m.m_diffuse << std::endl;
            os << "specular: " << m.m_specular << std::endl;
            os << "shininess: " << m.m_shininess << std::endl;
            os << "reflectiveness: " << m.m_reflectiveness << std::endl;
            os << "transparency: " << m.m_transparency << std::endl;
            os << "refractive index: " << m.m_refractive_index << std::endl;
            os << "pattern: " << m.m_pattern << std::endl;
            return os;
        }

    private:
        COAL::Color m_color = COAL::Color(1.0, 1.0, 1.0);
        COAL::Pattern m_pattern;
        double m_ambient = 0.1;
        double m_diffuse = 0.9;
        double m_specular = 0.9;
        double m_shininess = 200.0;
        double m_reflectiveness = 0.0;
        double m_transparency = 0.0;
        double m_refractive_index = 1.0;
    };
}; // namespace COAL
