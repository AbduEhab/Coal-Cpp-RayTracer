#pragma once

#include <Constants.h>
#include <Intersection.h>
#include <Material.h>
#include <Ray.h>
#include <Tuples/Point.h>
#include <Tuples/Vector.h>

struct Intersection;

namespace COAL
{
    struct XZPlane : public Shape
    {

        [[nodiscard]] std::vector<Intersection> intersects(const Ray &ray) const
        {

            PROFILE_FUNCTION();

            Ray transformed_ray = ray.transform(get_inverse_transform());

            if (std::abs(transformed_ray.m_direction.y) < kEpsilon)
            {
                return std::vector<Intersection>{};
            }

            double t = -transformed_ray.m_origin.y / transformed_ray.m_direction.y;

            if (t < 0)
            {
                return std::vector<Intersection>{};
            }

            return std::vector<Intersection>{Intersection(t, *this)};
        }

        [[nodiscard]] Vector normal_at([[maybe_unused]] const Point &p) const override
        {
            PROFILE_FUNCTION();

            return Vector(0, 1, 0);
        }

        // implement abstract equality
        [[nodiscard]] bool operator==(const Shape &other) const override
        {
            const auto other_xz_plane = dynamic_cast<const XZPlane *>(&other);
            return other_xz_plane != nullptr && other_xz_plane->get_transform() == get_transform();
        };
    };
}; // namespace COAL
