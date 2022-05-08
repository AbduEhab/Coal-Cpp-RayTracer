#pragma once

#include "Computation.h"
#include "Constants.h"
#include "Intersection.h"
#include "Lights/Light.h"
#include "Lights/PointLight.h"
#include "Matrix.h"
#include "Shapes/Shape.h"
#include "Shapes/Sphere.h"
#include "Tuples/Color.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace COAL
{
    struct World
    {

        _nodiscard World() = default;

        _nodiscard World(_maybe_unused const int type)
        {
            PROFILE_FUNCTION();

            std::shared_ptr<Sphere> sphere = std::make_shared<Sphere>(Sphere());
            sphere->set_material(Material(Color(0.8, 1, 0.6), -1.0, 0.7, 0.2, -1.0, nullptr, 0.0, -1.0, -1.0));
            m_shapes.emplace_back(sphere);

            std::shared_ptr<Sphere> sphere2 = std::make_shared<Sphere>(Sphere());
            sphere2->scale(0.5, 0.5, 0.5);
            m_shapes.emplace_back(sphere2);

            auto light = std::make_shared<PointLight>(PointLight());
            light->set_intensity(Color(1, 1, 1)).set_position(Point(-10, 10, -10));
            m_lights.emplace_back(light);
        }

        _nodiscard std::vector<Intersection> intersects(const Ray &ray) const
        {
            PROFILE_FUNCTION();

            std::vector<Intersection> res;

            for (const auto &shape : m_shapes)
            {
                std::vector<Intersection> shape_xs = shape->intersects(ray);
                res.insert(res.end(), shape_xs.begin(), shape_xs.end());
            }

            // lamda std::vector sort
            std::sort(res.begin(), res.end(), [](const Intersection &a, const Intersection &b)
                      { return a.m_t < b.m_t; });

            return res;
        }

        _nodiscard bool is_shadowed(const Point &point, const Light &light) const
        {
            PROFILE_FUNCTION();

            Vector v = light.m_position - point;
            double distance = v.magnitude();
            Vector direction = v.normalize();

            Ray ray(point, direction);
            auto xs = intersects(ray);

            Intersection hit = Intersection::hit(xs);

            if (hit.m_t >= 0 && hit.m_t < distance)
                return true;

            return false;
        }

        _nodiscard Color color_at(const Ray &ray) const
        {
            PROFILE_FUNCTION();

            auto xs = intersects(ray);
            Intersection hit = Intersection::hit(xs);

            if (hit.m_t < 0)
                return COAL::BLACK;

            Computation comps = hit.prepare_computation(ray, xs);

            return shade_hit(comps);
        }

        _nodiscard Color color_at(const Ray &ray, const int recursion_level) const
        {
            PROFILE_FUNCTION();

            auto xs = intersects(ray);
            Intersection hit = Intersection::hit(xs);

            if (hit.m_t < 0)
                return Color(0, 0, 0);

            Computation comps = hit.prepare_computation(ray, xs);

            return shade_hit(comps, recursion_level);
        }

        _nodiscard Color reflected_color(const Computation &comp, const int recursion_level = 0) const
        {
            PROFILE_FUNCTION();

            if (comp.m_s->m_material.get_reflectiveness() > 0 && recursion_level < MAX_DEPTH)
            {
                Ray reflected_ray = Ray(comp.m_over_point, comp.m_reflection_vector);
                Color reflected_color = color_at(reflected_ray, recursion_level + 1);
                return reflected_color * comp.m_s->m_material.get_reflectiveness();
            }

            return Color();
        }

        _nodiscard Color refraction_color(const Computation &comp, const int recursion_level = 0) const
        {
            PROFILE_FUNCTION();

            if (comp.m_s->m_material.get_refractive_index() > 0 && recursion_level < MAX_DEPTH)
            {
                double n_ratio = comp.m_inside ? comp.m_n1 / comp.m_n2 : comp.m_n2 / comp.m_n1;

                double cos_i = comp.m_eye_vector.dot(comp.m_normal_vector);

                double sin2_t = n_ratio * n_ratio * (1.0 - cos_i * cos_i);

                if (sin2_t > 1.0)
                    return Color();

                double cos_t = sqrt(1.0 - sin2_t);

                Vector direction = comp.m_normal_vector * (n_ratio * cos_i - cos_t) - comp.m_eye_vector * n_ratio;

                Ray refracted_ray = Ray(comp.m_under_point, direction);

                return color_at(refracted_ray, recursion_level + 1) * comp.m_s->m_material.get_transparency();
            }

            return Color();
        }

        _nodiscard Color shade_hit(const Computation &comp, const int depth = 0) const
        {

            Color res;

            for (const auto &light : m_lights)
            {
                bool in_shadow = is_shadowed(comp.m_over_point, *light);

                res = res + comp.m_s->m_material.lighting(
                                *light, *comp.m_s, comp.m_over_point, comp.m_eye_vector, comp.m_normal_vector, in_shadow);

                Color reflection_map = reflected_color(comp, depth + 1);

                Color refraction_map = refraction_color(comp, depth + 1);

                Material mat = comp.m_s->m_material;

                if (mat.get_reflectiveness() > 0 && mat.get_transparency() > 0)
                {
                    double reflectiveness = comp.schilck();

                    res = res + reflection_map * (1 - reflectiveness) + refraction_map * (1 - reflectiveness);
                }
                else
                    res = res + reflection_map + refraction_map;
            }
            return res;
        }

        // add shapes
        void add_shape(const std::shared_ptr<Shape> &shape)
        {
            PROFILE_FUNCTION();

            m_shapes.emplace_back(shape);
        }

        // add shapes
        void add_shapes(const std::vector<std::shared_ptr<Shape>> &shapes)
        {
            PROFILE_FUNCTION();

            m_shapes.insert(m_shapes.end(), shapes.begin(), shapes.end());
        }

        // add light
        void add_light(const std::shared_ptr<Light> &light)
        {
            PROFILE_FUNCTION();

            m_lights.emplace_back(light);
        }

        // add lights
        void add_lights(const std::vector<std::shared_ptr<Light>> &lights)
        {
            PROFILE_FUNCTION();

            m_lights.insert(m_lights.end(), lights.begin(), lights.end());
        }

        // get shapes
        const std::vector<std::shared_ptr<Shape>> &get_shapes() const
        {
            return m_shapes;
        }

        // get lights
        const std::vector<std::shared_ptr<Light>> &get_lights() const
        {
            return m_lights;
        }

    private:
        std::vector<std::shared_ptr<Shape>> m_shapes;
        std::vector<std::shared_ptr<Light>> m_lights;
        int MAX_DEPTH = 7;
    };

} // namespace COAL
