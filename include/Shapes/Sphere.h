#pragma once

#include <Constants.h>
#include <Intersection.h>
#include <Material.h>
#include <Matrix.h>
#include <Ray.h>
#include <Shapes/Shape.h>
#include <Tuples/Point.h>
#include <Tuples/Vector.h>

struct Intersection;

namespace COAL
{
    struct Sphere : public Shape
    {

        _nodiscard Sphere() = default;

        ~Sphere() = default;

        // generate default copy and move constructors
        Sphere(const Sphere &) = default;
        Sphere(Sphere &&) = default;

        _nodiscard std::vector<Intersection> intersects(const Ray &ray) const
        {
            PROFILE_FUNCTION();

            Ray transformed_ray = ray.transform(get_inverse_transform());

            Vector sphere_to_ray = transformed_ray.m_origin - Point();

            float a = transformed_ray.m_direction.dot(transformed_ray.m_direction);
            float b = 2 * sphere_to_ray.dot(transformed_ray.m_direction);
            float c = sphere_to_ray.dot(sphere_to_ray) - 1;

            float discriminant = b * b - 4 * a * c;

            if (discriminant < 0)
            {
                return {};
            }

            float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
            float t2 = (-b + std::sqrt(discriminant)) / (2 * a);

            if (t1 > t2)
            {
                std::swap(t1, t2);
            }

            if (t1 < 0)
            {
                t1 = t2;
            }

            if (t1 < 0)
            {
                return {};
            }

            return std::vector<Intersection>{Intersection(t1, *this), Intersection(t2, *this)};
        }

        _nodiscard Vector normal_at(const Point &p) const override
        {
            PROFILE_FUNCTION();

            Point object_point = get_inverse_transform() * p;
            Vector object_normal = (object_point - Point()).normalize();
            return (get_normal_transform() * object_normal).normalize();
        }

        // implement abstract equality
        _nodiscard bool operator==(const Shape &other) const override
        {
            const auto other_sphere = dynamic_cast<const Sphere *>(&other);
            return other_sphere != nullptr && other_sphere->get_transform() == get_transform();
        }

        // get name
        _nodiscard const char *get_name() const override
        {
            return "Sphere ";
        }
    };

    _nodiscard _maybe_unused static Sphere glass_sphere()
    {
        return static_cast<Sphere &>(Sphere().set_material(Material().set_transparency(1.0).set_refractive_index(1.5)));
    }
}; // namespace COAL
