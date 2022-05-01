#pragma once

#include "Shapes/Shape.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

struct Shape;

namespace COAL
{
    struct Computation
    {

        [[nodiscard]] constexpr Computation(const double t, const Shape &s, const Point &p, const Vector &eye_vector, const Vector &normal_vector,
                                            const bool inside, const Point &over_point, const Vector &reflection_vector, const double n1, const double n2, const Point &under_point)
            : m_t(t), m_s(&s), m_p(p), m_eye_vector(eye_vector), m_normal_vector(normal_vector), m_inside(inside), m_over_point(over_point),
              m_reflection_vector(reflection_vector), m_n1(n1), m_n2(n2), m_under_point(under_point)
        {
        }

        [[nodiscard]] constexpr double schilck() const noexcept
        {
            double cosine = m_eye_vector.dot(m_normal_vector);

            if (m_n1 > m_n2)
            {
                double n = m_n1 / m_n2;
                double sine2_t = n * n * (1 - cosine * cosine);

                if (sine2_t > 1)
                {
                    return 1;
                }

                double cos_t = sqrt(1 - sine2_t);

                cosine = cos_t;
            }

            double r0 = ((m_n1 - m_n2) / (m_n1 + m_n2));
            r0 = r0 * r0;

            return r0 + (1 - r0) * pow((1 - cosine), 5);
        }

        double m_t;
        const Shape *m_s;
        Point m_p;
        Vector m_eye_vector;
        Vector m_normal_vector;
        bool m_inside;
        Point m_over_point;
        Vector m_reflection_vector;
        double m_n1;
        double m_n2;
        Point m_under_point;
    };
} // namespace COAL
