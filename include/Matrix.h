#pragma once

#include "Constants.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace COAL
{
    struct Matrix4
    {

        [[nodiscard]] constexpr Matrix4(){};

        [[nodiscard]] constexpr Matrix4(const double *array, _maybe_unused int array_size)
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

        [[nodiscard]] constexpr Matrix4(const std::vector<std::vector<double>> &values)
        {
            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    this->_matrix[i][j] = values[i][j];
        }

        // constructor for (double, double, double, int, double, double, double, int, double, double, double, double, double, double, double, double)
        [[nodiscard]] constexpr Matrix4(const double a00, const double a01, const double a02, const double a03, const double a10, const double a11, const double a12, const double a13, const double a20, const double a21, const double a22, const double a23, const double a30, const double a31, const double a32, const double a33)
        {
            this->_matrix[0][0] = a00;
            this->_matrix[0][1] = a01;
            this->_matrix[0][2] = a02;
            this->_matrix[0][3] = a03;
            this->_matrix[1][0] = a10;
            this->_matrix[1][1] = a11;
            this->_matrix[1][2] = a12;
            this->_matrix[1][3] = a13;
            this->_matrix[2][0] = a20;
            this->_matrix[2][1] = a21;
            this->_matrix[2][2] = a22;
            this->_matrix[2][3] = a23;
            this->_matrix[3][0] = a30;
            this->_matrix[3][1] = a31;
            this->_matrix[3][2] = a32;
            this->_matrix[3][3] = a33;
        }

        // // [][] operator
        // [[nodiscard]] constexpr double &operator[](const int index) noexcept
        // {
        //     return this->_matrix[index / 4][index % 4];
        // }

        // [] operator
        [[nodiscard]] constexpr double *operator[](const int index) noexcept
        {
            return this->_matrix[index];
        }

        // / operator
        [[nodiscard]] constexpr Matrix4 operator/(const double rhs) const noexcept
        {
            return Matrix4(
                this->_matrix[0][0] / rhs, this->_matrix[0][1] / rhs, this->_matrix[0][2] / rhs, this->_matrix[0][3] / rhs,
                this->_matrix[1][0] / rhs, this->_matrix[1][1] / rhs, this->_matrix[1][2] / rhs, this->_matrix[1][3] / rhs,
                this->_matrix[2][0] / rhs, this->_matrix[2][1] / rhs, this->_matrix[2][2] / rhs, this->_matrix[2][3] / rhs,
                this->_matrix[3][0] / rhs, this->_matrix[3][1] / rhs, this->_matrix[3][2] / rhs, this->_matrix[3][3] / rhs);
        }

        // == operator
        [[nodiscard]] constexpr bool operator==(const Matrix4 &other) const noexcept
        {
            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    if ((std::abs(this->_matrix[i][j] - other._matrix[i][j]) <= 0.00001))
                        return false;

            return true;
        }

        // != operator
        [[nodiscard]] constexpr bool operator!=(const Matrix4 &other) const noexcept
        {
            return !(*this == other);
        }

        // + operator
        [[nodiscard]] constexpr Matrix4 operator+(const Matrix4 &other) const noexcept
        {
            Matrix4 result;

            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    result._matrix[i][j] = this->_matrix[i][j] + other._matrix[i][j];

            return result;
        }

        // - operator
        [[nodiscard]] constexpr Matrix4 operator-(const Matrix4 &other) const noexcept
        {
            Matrix4 result;

            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    result._matrix[i][j] = this->_matrix[i][j] - other._matrix[i][j];

            return result;
        }

        // * by std::vector<std::vector<double>>
        [[nodiscard]] constexpr Matrix4 operator*(const std::vector<std::vector<double>> &other) const noexcept
        {
            Matrix4 result;

            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    result._matrix[i][j] = this->_matrix[i][0] * other[0][j] + this->_matrix[i][1] * other[1][j] + this->_matrix[i][2] * other[2][j] + this->_matrix[i][3] * other[3][j];

            return result;
        }
        // * operator
        [[nodiscard]] constexpr Matrix4 operator*(const Matrix4 &other) const noexcept
        {
            Matrix4 result;

            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    result._matrix[i][j] = this->_matrix[i][0] * other._matrix[0][j] +
                                           this->_matrix[i][1] * other._matrix[1][j] +
                                           this->_matrix[i][2] * other._matrix[2][j] +
                                           this->_matrix[i][3] * other._matrix[3][j];

            return result;
        }

        // * operator
        [[nodiscard]] constexpr Matrix4 operator*(const double &other) const noexcept
        {
            Matrix4 result;

            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    result._matrix[i][j] = this->_matrix[i][j] * other;

            return result;
        }

        // multiply vector3 by matrix and return a vector3
        [[nodiscard]] constexpr COAL::Vector operator*(const COAL::Vector &other) const noexcept
        {
            COAL::Vector result;

            result.x = this->_matrix[0][0] * other.x + this->_matrix[0][1] * other.y +
                       this->_matrix[0][2] * other.z;
            result.y = this->_matrix[1][0] * other.x + this->_matrix[1][1] * other.y +
                       this->_matrix[1][2] * other.z;
            result.z = this->_matrix[2][0] * other.x + this->_matrix[2][1] * other.y +
                       this->_matrix[2][2] * other.z;

            return result;
        }

        [[nodiscard]] constexpr COAL::Point operator*(const COAL::Point &other) const noexcept
        {
            COAL::Point result;

            result.x = this->_matrix[0][0] * other.x + this->_matrix[0][1] * other.y +
                       this->_matrix[0][2] * other.z + this->_matrix[0][3];
            result.y = this->_matrix[1][0] * other.x + this->_matrix[1][1] * other.y +
                       this->_matrix[1][2] * other.z + this->_matrix[1][3];
            result.z = this->_matrix[2][0] * other.x + this->_matrix[2][1] * other.y +
                       this->_matrix[2][2] * other.z + this->_matrix[2][3];

            return result;
        }

        // *= operator
        [[nodiscard]] constexpr Matrix4 &operator*=(const Matrix4 &other) noexcept
        {
            *this = *this * other;

            return *this;
        }

        // *= operator
        [[nodiscard]] constexpr Matrix4 &operator*=(const double &other) noexcept
        {
            *this = *this * other;

            return *this;
        }

        // *= operator
        [[nodiscard]] constexpr Matrix4 &operator+=(const Matrix4 &other) noexcept
        {
            *this = *this + other;

            return *this;
        }

        // *= operator
        [[nodiscard]] constexpr Matrix4 &operator-=(const Matrix4 &other) noexcept
        {
            *this = *this - other;

            return *this;
        }

        // [] operator
        [[nodiscard]] constexpr const double &operator[](const int index) const noexcept
        {
            return this->_matrix[index / 4][index % 4];
        }

        // [] operator
        [[nodiscard]] constexpr const double &operator()(const int row, const int column) const noexcept
        {
            return this->_matrix[row][column];
        }

        // transpose
        [[nodiscard]] constexpr Matrix4 transpose() const noexcept
        {
            Matrix4 result;

            for (char i = 0; i < 4; i++)
                for (char j = 0; j < 4; j++)
                    result._matrix[i][j] = this->_matrix[j][i];

            return result;
        }

        // determinant
        [[nodiscard]] constexpr double determinant4() const noexcept
        {
            return this->_matrix[0][0] * this->_matrix[1][1] * this->_matrix[2][2] * this->_matrix[3][3] +
                   this->_matrix[0][0] * this->_matrix[1][2] * this->_matrix[2][3] * this->_matrix[3][1] +
                   this->_matrix[0][0] * this->_matrix[1][3] * this->_matrix[2][1] * this->_matrix[3][2] +
                   this->_matrix[0][1] * this->_matrix[1][0] * this->_matrix[2][3] * this->_matrix[3][2] +
                   this->_matrix[0][1] * this->_matrix[1][2] * this->_matrix[2][0] * this->_matrix[3][3] +
                   this->_matrix[0][1] * this->_matrix[1][3] * this->_matrix[2][2] * this->_matrix[3][0] +
                   this->_matrix[0][2] * this->_matrix[1][0] * this->_matrix[2][1] * this->_matrix[3][3] +
                   this->_matrix[0][2] * this->_matrix[1][1] * this->_matrix[2][3] * this->_matrix[3][0] +
                   this->_matrix[0][2] * this->_matrix[1][3] * this->_matrix[2][0] * this->_matrix[3][1] +
                   this->_matrix[0][3] * this->_matrix[1][0] * this->_matrix[2][2] * this->_matrix[3][1] +
                   this->_matrix[0][3] * this->_matrix[1][1] * this->_matrix[2][0] * this->_matrix[3][2] +
                   this->_matrix[0][3] * this->_matrix[1][2] * this->_matrix[2][1] * this->_matrix[3][0] -
                   this->_matrix[0][0] * this->_matrix[1][1] * this->_matrix[2][3] * this->_matrix[3][2] -
                   this->_matrix[0][0] * this->_matrix[1][2] * this->_matrix[2][1] * this->_matrix[3][3] -
                   this->_matrix[0][0] * this->_matrix[1][3] * this->_matrix[2][2] * this->_matrix[3][1] -
                   this->_matrix[0][1] * this->_matrix[1][0] * this->_matrix[2][2] * this->_matrix[3][3] -
                   this->_matrix[0][1] * this->_matrix[1][2] * this->_matrix[2][3] * this->_matrix[3][0] -
                   this->_matrix[0][1] * this->_matrix[1][3] * this->_matrix[2][0] * this->_matrix[3][2] -
                   this->_matrix[0][2] * this->_matrix[1][0] * this->_matrix[2][3] * this->_matrix[3][1] -
                   this->_matrix[0][2] * this->_matrix[1][1] * this->_matrix[2][0] * this->_matrix[3][3] -
                   this->_matrix[0][2] * this->_matrix[1][3] * this->_matrix[2][1] * this->_matrix[3][0] -
                   this->_matrix[0][3] * this->_matrix[1][0] * this->_matrix[2][1] * this->_matrix[3][2] -
                   this->_matrix[0][3] * this->_matrix[1][1] * this->_matrix[2][2] * this->_matrix[3][0] -
                   this->_matrix[0][3] * this->_matrix[1][2] * this->_matrix[2][0] * this->_matrix[3][1];
        }

        template <size_t size>
        _nodiscard constexpr void sub_matrix(const double (&matrix)[size + 1][size + 1], const int row, const int column, double (&sub_matrix)[size][size]) const
        {
            bool a_replaced = false;
            bool b_replaced = false;

            for (char i = 0; i < size + 1; i++)
            {
                b_replaced = false;
                if (i != row)
                    for (char j = 0; j < size + 1; j++)
                    {
                        if (j != column)
                            sub_matrix[a_replaced ? i - 1 : i][b_replaced ? j - 1 : j] = matrix[i][j];
                        else
                            b_replaced = true;
                    }
                else
                    a_replaced = true;
            }
        }

        [[nodiscard]] double constexpr determinant(const double (&matrix)[2][2]) const
        {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }

        [[nodiscard]] double constexpr determinant(const double (&matrix)[3][3]) const
        {
            double det = 0;

            for (char i = 0; i < 3; i++)
            {
                if (i % 2 == 0)
                {
                    double temp_matrix[2][2];
                    sub_matrix<2>(matrix, i, 0, temp_matrix);
                    det += matrix[i][0] * determinant(temp_matrix);
                }
                else
                {
                    double temp_matrix[2][2];
                    sub_matrix<2>(matrix, i, 0, temp_matrix);
                    det -= matrix[i][0] * determinant(temp_matrix);
                }
            }

            return det;
        }

        // cofactor
        [[nodiscard]] constexpr Matrix4 cofactor() const noexcept
        {
            Matrix4 cofactor;

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    double temp_matrix[3][3];
                    sub_matrix<3>(_matrix, i, j, temp_matrix);

                    cofactor[i][j] = pow(-1, i + j) * determinant(temp_matrix);
                }
            }

            return cofactor;
        }

        // matrix adjugate
        [[nodiscard]] constexpr Matrix4 adjugate() const noexcept
        {
            return this->cofactor().transpose();
        }

        // matrix inverse
        [[nodiscard]] constexpr Matrix4 inverse() const noexcept
        {
            return this->adjugate() / this->determinant4();
        }

        _nodiscard Matrix4 translate(std::vector<double> const &values) const
        {
            std::vector<std::vector<double>> translation_values = {
                {1, 0, 0, values[0]},
                {0, 1, 0, values[1]},
                {0, 0, 1, values[2]},
                {0, 0, 0, 1},
            };

            return *this * translation_values;
        }

        _nodiscard Matrix4 translate(const double x, const double y, const double z) const
        {
            std::vector<std::vector<double>> translation_values = {
                {1, 0, 0, x},
                {0, 1, 0, y},
                {0, 0, 1, z},
                {0, 0, 0, 1},
            };

            return *this * translation_values;
        }

        _nodiscard Matrix4 scale(std::vector<double> const &values) const
        {
            std::vector<std::vector<double>> translation_values = {
                {values[0], 0, 0, 0},
                {0, values[1], 0, 0},
                {0, 0, values[2], 0},
                {0, 0, 0, 1},
            };

            return *this * translation_values;
        }

        _nodiscard Matrix4 scale(const double x, const double y, const double z) const
        {
            std::vector<std::vector<double>> translation_values = {
                {x, 0, 0, 0},
                {0, y, 0, 0},
                {0, 0, z, 0},
                {0, 0, 0, 1},
            };

            return *this * translation_values;
        }

        _nodiscard Matrix4 rotate_x(const double radians) const
        {
            std::vector<std::vector<double>> rotate_x_values = {
                {1, 0, 0, 0},
                {0, std::cos(radians), -std::sin(std::cos(radians)), 0},
                {0, std::sin(std::cos(radians)), std::cos(radians), 0},
                {0, 0, 0, 1},
            };

            return *this * rotate_x_values;
        }

        _nodiscard Matrix4 rotate_y(const double radians) const
        {
            std::vector<std::vector<double>> rotate_y_values = {
                {std::cos(radians), 0, std::sin(radians), 0},
                {0, 1, 0, 0},
                {-std::sin(radians), 0, std::cos(radians), 0},
                {0, 0, 0, 1},
            };

            return *this * rotate_y_values;
        }

        _nodiscard Matrix4 rotate_z(const double radians) const
        {
            std::vector<std::vector<double>> rotate_z_values = {
                {std::cos(radians), -std::sin(radians), 0, 0},
                {std::sin(radians), std::cos(radians), 0, 0},
                {0, 0, 1, 0},
                {0, 0, 0, 1},
            };

            return *this * rotate_z_values;
        }

        _nodiscard Matrix4 shear(double Xy, double Xz, double Yx, double Yz, double Zx, double Zy) const
        {
            std::vector<std::vector<double>> shear_values = {
                {1, Xy, Xz, 0},
                {Yx, 1, Yz, 0},
                {Zx, Zy, 1, 0},
                {0, 0, 0, 1},
            };

            return *this * shear_values;
        }

        // << operator
        friend std::ostream &operator<<(std::ostream &os, const Matrix4 &m)
        {
            os << "[" << m._matrix[0][0] << " " << m._matrix[0][1] << " " << m._matrix[0][2] << " " << m._matrix[0][3] << "]" << std::endl;
            os << "[" << m._matrix[1][0] << " " << m._matrix[1][1] << " " << m._matrix[1][2] << " " << m._matrix[1][3] << "]" << std::endl;
            os << "[" << m._matrix[2][0] << " " << m._matrix[2][1] << " " << m._matrix[2][2] << " " << m._matrix[2][3] << "]" << std::endl;
            os << "[" << m._matrix[3][0] << " " << m._matrix[3][1] << " " << m._matrix[3][2] << " " << m._matrix[3][3] << "]" << std::endl;

            return os;
        }

        // >> operator
        friend std::istream &operator>>(std::istream &is, Matrix4 &m)
        {
            for (char i = 0; i < 4; i++)
            {
                for (char j = 0; j < 4; j++)
                {
                    is >> m._matrix[i][j];
                }
            }

            return is;
        }

    private:
        double _matrix[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
        static constexpr double _identity_array[4][4] = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
    };

    constexpr const Matrix4 IDENTITY = Matrix4();
}; // namespace CLOAL