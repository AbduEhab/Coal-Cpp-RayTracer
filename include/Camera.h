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

        _nodiscard Camera(int hSize, int vSize, double fov) : m_hsize(hSize), m_vsize(vSize), m_field_of_view(fov), m_half_height(0), m_half_width(0), m_pixel_size(0)
        {
            set_pixel_size();
        }

        _nodiscard void set_pixel_size()
        {
            double half_view = std::tan(m_field_of_view / 2.0);
            double aspect = m_hsize / (m_vsize + 0.0);

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

            m_pixel_size = (m_half_width * 2) / m_hsize;
        }

        _nodiscard Matrix4 transform(Point &from, Point &to, Vector &up)
        {
            Vector forword = (to - from).normalize();

            Vector left = forword.cross(up).normalize();

            Vector new_up = left.cross(forword);

            Matrix4 orientation(left.x, left.y, left.z, 0,
                                new_up.x, new_up.y, new_up.z, 0,
                                forword.x, forword.y, forword.z, 0,
                                0, 0, 0, 1);

            m_transform = orientation.translate(-from.x, -from.y, -from.z);

            m_inverse_transform = m_transform.inverse();

            return m_transform;
        }

        _nodiscard Ray ray_for_pixel(int x, int y) const
        {
            double xOffset = (x - (m_hsize / 2.0)) * m_pixel_size;
            double yOffset = (y - (m_vsize / 2.0)) * m_pixel_size;

            double world_x = m_half_width - xOffset;
            double world_y = m_half_height - yOffset;

            Point pixel = m_inverse_transform * Point(world_x, world_y, -1);
            Point origin = m_inverse_transform * Point(0, 0, 0);
            Vector direction = (pixel - origin).normalize();

            return Ray(origin, direction);
        }

        _nodiscard Color **classic_render(World &w) const
        {
            Color **image;
            image = new Color *[500];
            for (int i = 0; i < 500; i++)
                image[i] = new Color[500];

            for (int y = 0; y < m_vsize; y++)
            {

                std::cout << y << std::endl;
                for (int x = 0; x < m_hsize; x++)
                {
                    Ray r = ray_for_pixel(x, y);

                    Color c = w.color_at(r);

                    image[y][x] = c;
                }
            }

            return image;
        }

        // generate getters
        _nodiscard int get_hsize() const
        {
            return m_hsize;
        }

        _nodiscard int get_vsize() const
        {
            return m_vsize;
        }

        _nodiscard double get_field_of_view() const
        {
            return m_field_of_view;
        }

        _nodiscard double get_half_height() const
        {
            return m_half_height;
        }

        _nodiscard double get_half_width() const
        {
            return m_half_width;
        }

        _nodiscard double get_pixel_size() const
        {
            return m_pixel_size;
        }

        _nodiscard const Matrix4 &get_transform() const
        {
            return m_transform;
        }

        _nodiscard const Matrix4 &get_inverse_transform() const
        {
            return m_inverse_transform;
        }

        // generate setters
        void set_hsize(int hsize)
        {
            m_hsize = hsize;
            set_pixel_size();
        }

        void set_vsize(int vsize)
        {
            m_vsize = vsize;
            set_pixel_size();
        }

        void set_field_of_view(double field_of_view)
        {
            m_field_of_view = field_of_view;
            set_pixel_size();
        }

        void set_half_height(double half_height)
        {
            m_half_height = half_height;
        }

        void set_half_width(double half_width)
        {
            m_half_width = half_width;
        }

        void set_pixel_size(double pixel_size)
        {
            m_pixel_size = pixel_size;
        }

        void set_transform(const Matrix4 &transform)
        {
            m_transform = transform;
        }

        void set_inverse_transform(const Matrix4 &inverse_transform)
        {
            m_inverse_transform = inverse_transform;
        }

    private:
        int m_hsize;
        int m_vsize;
        double m_field_of_view;
        double m_pixel_size;
        Matrix4 m_transform = COAL::IDENTITY;
        Matrix4 m_inverse_transform = COAL::IDENTITY;

        double m_half_width;
        double m_half_height;
    };
} // namespace COAL
