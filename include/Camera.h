#pragma once

#include "Constants.h"
#include "Matrix.h"
#include "Tuples/Color.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"
#include "World.h"

namespace COAL
{
    struct Camera
    {

        _nodiscard Camera(int width, int height, float fov) : m_width(width), m_height(height), m_field_of_view(fov), m_half_height(0), m_half_width(0), m_pixel_size(0)
        {
            set_pixel_size();
        }

        _nodiscard void set_pixel_size()
        {
            PROFILE_FUNCTION();

            float half_view = std::tan(m_field_of_view / 2.0f);
            float aspect = m_width / (m_height + 0.0f);

            if (aspect >= 1.0)
            {
                m_half_width = half_view;
                m_half_height = half_view / aspect;
            }
            else
            {
                m_half_width = half_view / aspect;
                m_half_height = half_view;
            }

            m_pixel_size = (m_half_width * 2) / m_width;
        }

        _nodiscard void transform(const Point &from, const Point &to, const Vector &up)
        {
            PROFILE_FUNCTION();

            Vector forword = (to - from).normalize();

            Vector left = forword.cross(up).normalize();

            Vector new_up = left.cross(forword);

            Matrix4 orientation(left.x, left.y, left.z, 0,
                                new_up.x, new_up.y, new_up.z, 0,
                                -forword.x, -forword.y, -forword.z, 0,
                                0, 0, 0, 1);

            m_transform = orientation.translate(-from.x, -from.y, -from.z);

            m_inverse_transform = m_transform.inverse();
        }

        _nodiscard Ray ray_for_pixel(int x, int y) const
        {
            PROFILE_FUNCTION();

            float xOffset = (x + 0.5f) * m_pixel_size;
            float yOffset = (y + 0.5f) * m_pixel_size;

            float world_x = m_half_width - xOffset;
            float world_y = m_half_height - yOffset;

            Point pixel = m_inverse_transform * Point(world_x, world_y, -1);
            Point origin = m_inverse_transform * Point(0, 0, 0);
            Vector direction = (pixel - origin).normalize();

            return Ray(origin, direction);
        }

        template <size_t width, size_t hight>
        _nodiscard void classic_render(World &w, Color (&canvas)[width][hight]) const
        {
            PROFILE_FUNCTION();

            for (int y = 0; y < m_height; y++)
            {
                std::cout << y << std::endl;
                for (int x = 0; x < m_width; x++)
                {
                    Ray r = ray_for_pixel(x, y);

                    Color c = w.color_at(r);

                    canvas[y][x] = c;
                }
            }
        }

        _nodiscard Color **classic_render(World &w) const
        {
            PROFILE_FUNCTION();

            debug_print("Started Single-Threaded Rendering");

            Timer timer;

            Color **image;
            image = new Color *[m_width];
            for (int i = 0; i < m_width; i++)
                image[i] = new Color[m_height];

            for (int y = 0; y < m_height; y++)
            {

                std::cout << ">> Thread {" + std::to_string(y + 1) + "}: Calculating Row: [" + std::to_string(y + 1) + '/' + std::to_string(m_height) + ']' << std::endl;

                for (int x = 0; x < m_width; x++)
                {
                    Ray r = ray_for_pixel(x, y);

                    Color c = w.color_at(r);

                    image[y][x] = c;
                }
            }

            debug_print("Single-Threaded Rendering done in: " + std::to_string(timer.elapsed_millis()) + " ms");

            return image;
        }

        _nodiscard std::shared_ptr<Color[]> classic_render_multi_threaded(World &w, const int thread_count = kCORE_COUNT)
        {
            PROFILE_FUNCTION();

            m_is_finished = false;

            debug_print("Started Multi-Threaded Rendering");

            Timer timer;

            std::shared_ptr<Color[]> image(new Color[m_width * m_height]);

            std::vector<std::thread> threads;

            for (int i = 0; i < thread_count; i++)
            {
                const int index = i;

                threads.push_back(std::thread([&, index]()
                                                                            {
                    for (int y = index; y < m_height; y += thread_count)
                    {
                        debug_print(">> Thread {" + std::to_string(index + 1) + "}: Calculating Row: [" + std::to_string(y + 1) + '/' + std::to_string(m_height) + "]");

                        for (int x = 0; x < m_width; x++)
                        {
                            Ray r = ray_for_pixel(x, y);

                            Color c = w.color_at(r);

                            image.get() [y *m_width + x] = c;
                        }
                    } }));
            }

            for (auto &t : threads)
                t.join();

            m_is_finished = true;

            debug_print("Multi-Threaded Rendering done in: " + std::to_string(timer.elapsed_millis()) + " ms");

            return image;
        }

        // generate getters
        _nodiscard constexpr int is_finished() const
        {
            return m_is_finished;
        }

        _nodiscard constexpr int get_width() const
        {
            return m_width;
        }

        _nodiscard constexpr int get_height() const
        {
            return m_height;
        }

        _nodiscard constexpr float get_field_of_view() const
        {
            return m_field_of_view;
        }

        _nodiscard constexpr float get_half_height() const
        {
            return m_half_height;
        }

        _nodiscard constexpr float get_half_width() const
        {
            return m_half_width;
        }

        _nodiscard constexpr float get_pixel_size() const
        {
            return m_pixel_size;
        }

        _nodiscard constexpr const Matrix4 &get_transform() const
        {
            return m_transform;
        }

        _nodiscard constexpr const Matrix4 &get_inverse_transform() const
        {
            return m_inverse_transform;
        }

        // generate setters
        void set_width(int width)
        {
            m_width = width;
            set_pixel_size();
        }

        void set_height(int height)
        {
            m_height = height;
            set_pixel_size();
        }

        void set_field_of_view(float field_of_view)
        {
            m_field_of_view = field_of_view;
            set_pixel_size();
        }

        void constexpr set_half_height(float half_height)
        {
            m_half_height = half_height;
        }

        void constexpr set_half_width(float half_width)
        {
            m_half_width = half_width;
        }

        void constexpr set_pixel_size(float pixel_size)
        {
            m_pixel_size = pixel_size;
        }

        void constexpr set_transform(const Matrix4 &transform)
        {
            m_transform = transform;
        }

        void constexpr set_inverse_transform(const Matrix4 &inverse_transform)
        {
            m_inverse_transform = inverse_transform;
        }

    private:
        bool m_is_finished = false;
        int m_width;
        int m_height;
        float m_field_of_view;
        float m_pixel_size;
        Matrix4 m_transform = COAL::IDENTITY;
        Matrix4 m_inverse_transform = COAL::IDENTITY;

        float m_half_width;
        float m_half_height;
    };
} // namespace COAL
