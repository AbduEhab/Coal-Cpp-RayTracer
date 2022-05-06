#pragma once

#include "Intersection.h"
#include "Material.h"
#include "Matrix.h"
#include "Ray.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace COAL
{

    struct Intersection;

    struct Shape
    {

        [[nodiscard]] virtual std::vector<Intersection> intersects(const Ray &ray) const = 0;

        [[nodiscard]] virtual Vector normal_at(const Point &p) const = 0;

        // setters and getters
        [[nodiscard]] const Material &get_material() const
        {
            return m_material;
        }

        [[nodiscard]] constexpr const Matrix4 &get_transform() const
        {
            return m_transform;
        }

        [[nodiscard]] constexpr const Matrix4 &get_inverse_transform() const
        {
            return m_inverse_transform;
        }

        [[nodiscard]] constexpr const Matrix4 &get_normal_transform() const
        {
            return m_normal_transform;
        }

        [[nodiscard]] constexpr const Matrix4 &get_inverse_normal_transform() const
        {
            return m_inverse_normal_transform;
        }

        // abstract equality
        [[nodiscard]] virtual bool operator==(const Shape &other) const = 0;

        Shape &set_material(const Material &material)
        {
            m_material = material;

            return *this;
        }

        Shape &set_transform(const Matrix4 &transform)
        {
            m_transform = transform;
            m_inverse_transform = m_transform.inverse();
            m_normal_transform = m_inverse_transform.transpose();
            m_inverse_normal_transform = m_normal_transform.inverse();

            return *this;
        }

        Shape &set_transform(const Matrix4 &transform, const Matrix4 &inverse_transform)
        {
            m_transform = transform;
            m_inverse_transform = inverse_transform;
            m_normal_transform = m_inverse_transform.transpose();
            m_inverse_normal_transform = m_normal_transform.inverse();

            return *this;
        }

        Shape &set_transform(const Matrix4 &transform, const Matrix4 &inverse_transform, const Matrix4 &normal_transform, const Matrix4 &inverse_normal_transform)
        {
            m_transform = transform;
            m_inverse_transform = inverse_transform;
            m_normal_transform = normal_transform;
            m_inverse_normal_transform = inverse_normal_transform;

            return *this;
        }

        // private:
        COAL::Material m_material = COAL::Material();
        COAL::Matrix4 m_transform = COAL::IDENTITY;
        COAL::Matrix4 m_inverse_transform = COAL::IDENTITY;
        COAL::Matrix4 m_normal_transform = COAL::IDENTITY;
        COAL::Matrix4 m_inverse_normal_transform = COAL::IDENTITY;
    };

    [[nodiscard]] COAL::Color Pattern::colot_at(const Shape &s, const COAL::Point &p) const
    {
        PROFILE_FUNCTION();

        Point object_point = s.get_transform().inverse() * p;
        Point pattern_point = m_transform.inverse() * object_point;

        return color_at(pattern_point);
    }
} // namespace COAL
