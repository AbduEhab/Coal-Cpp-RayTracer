#pragma once

#include "Constants.h"
#include "Tuples/Point.h"
#include "Tuples/Vector.h"

namespace COAL
{
    class Matrix4
    {

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
        [[nodiscard]] constexpr double determinant() const noexcept
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

        // matrix sub-determinant
        [[nodiscard]] constexpr double sub_determinant(int i, int j) const noexcept
        {
            double det = 0;

            double temp[3][3] = {};

            for (char k = 0; k < 3; k++)
            {
                for (char l = 0; l < 3; l++)
                {
                    temp[k][l] = _matrix[(k + 1) % 3][(l + 1) % 3];
                }
            }

            det += _matrix[i][j] * temp[0][0] * sub_determinant(0, 0);
            det -= _matrix[i][j] * temp[0][1] * sub_determinant(0, 1);
            det += _matrix[i][j] * temp[0][2] * sub_determinant(0, 2);

            return det;
        }

        // matrix cofactor
        [[nodiscard]] constexpr Matrix4 cofactor() const noexcept
        {
            Matrix4 temp = Matrix4();

            for (char i = 0; i < 4; i++)
            {
                for (char j = 0; j < 4; j++)
                {
                    temp._matrix[i][j] = sub_determinant(i, j);
                }
            }

            return temp;
        }

        // matrix adjugate
        [[nodiscard]] constexpr Matrix4 adjugate() const noexcept
        {
            Matrix4 temp = cofactor();

            for (char i = 0; i < 4; i++)
            {
                for (char j = 0; j < 4; j++)
                {
                    temp._matrix[i][j] = temp._matrix[i][j] * ((i + j) % 2 == 0 ? 1 : -1);
                }
            }

            return temp;
        }

        // matrix inverse
        [[nodiscard]] constexpr Matrix4 inverse() const noexcept
        {
            return adjugate().transpose();
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

    static constexpr const Matrix4 IDENTITY = Matrix4();
}; // namespace CLOAL