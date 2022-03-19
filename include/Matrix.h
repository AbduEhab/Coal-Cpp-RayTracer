#pragma once

#include "Constants.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace CLOAL
{
    class Matrix4
    {
    private:
        class Matrix3
        {
            [[nodiscard]] constexpr Matrix3(){};

            double _matrix[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        };

    public:
        [[nodiscard]] constexpr Matrix4(){};

        [[nodiscard]] constexpr Matrix4(const double *array, int array_size)
        {
            assert(16 == array_size);

            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    this->_matrix[i][j] = array[i * 4 + j];
        }

        [[nodiscard]] constexpr Matrix4(const std::array<std::array<double, 4>, 4> &array)
        {
            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    this->_matrix[i][j] = array[i][j];
        }

        [[nodiscard]] constexpr int operator==(const Matrix4 &b) const noexcept
        {
            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    if (std::abs(_matrix[i][j] - b._matrix[i][j]) > 0.00001)
                        return 1;

            return 0;
        }

        [[nodiscard]] constexpr COAL::Point operator*(const COAL::Point &p) const noexcept
        {
            double res[4] = {};

            double mb[4] = {p.x, p.y, p.z, 1};

            for (int i = 0; i < 3; i++)
            {
                double temp = 0;
                for (int j = 0; j < 4; j++)
                {
                    temp += _matrix[i][j] * mb[j];
                }
                res[i] = temp;
            }

            return COAL::Point(res[0], res[1], res[2]);
        }

        [[nodiscard]] constexpr COAL::Vector operator*(const COAL::Vector &v) const noexcept
        {
            double res[4] = {};

            double mb[4] = {v.x, v.y, v.z, 0};

            for (int i = 0; i < 3; i++)
            {
                double temp = 0;
                for (int j = 0; j < 4; j++)
                {
                    temp += _matrix[i][j] * mb[j];
                }
                res[i] = temp;
            }

            return COAL::Vector(res[0], res[1], res[2]);
        }

        [[nodiscard]] constexpr Matrix4 transpose() const noexcept
        {
            Matrix4 temp = Matrix4();

            for (char i = 0; i < 4; i++)
            {
                for (char j = 0; j < 4; j++)
                {
                    temp._matrix[i][j] = _matrix[j][i];
                }
            }
            return temp;
        }

        [[nodiscard]] constexpr double determinant()  noexcept
        {
            return determinantHelper(*this);
        }

    private:
        [[nodiscard]] constexpr double determinantHelper(Matrix4 &matrix) const noexcept
        {
            double res = 0;

            for (int i = 0; i < 4; i++)
            {
                if (i % 2 == 0)
                    res += matrix[i][0] * determinantHelper(matrix.subMatrix(i, 0));
                else
                    res -= matrix[i][0] * determinantHelper(matrix.subMatrix(i, 0));
            }
            return res;
        }

        [[nodiscard]] constexpr Matrix3 subMatrix(int a, int b) const noexcept
        {
        }
        //     Matrix temp = new Matrix(this.size - 1);
        //     boolean aReplaced = false;
        //     boolean bReplaced = false;
        //     for (int i = 0; i < size; i++) {
        //         bReplaced = false;
        //         if (i != a)
        //             for (int j = 0; j < size; j++) {
        //                 if (j != b)
        //                     temp.setElement(aReplaced ? i - 1 : i, bReplaced ? j - 1 : j, matrix[i][j]);
        //                 else
        //                     bReplaced = true;
        //             }
        //         else
        //             aReplaced = true;
        //     }
        //     return temp;
        // }

    private:
        double _matrix[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
        static constexpr double _identity_array[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    };

    static constexpr const Matrix4 IDENTITY = Matrix4();
}; // namespace CLOAL