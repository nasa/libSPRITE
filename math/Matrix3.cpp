#include <string.h>
#include "math/DCM.h"
#include "math/Matrix3.h"
#include "math/Vec3.h"

namespace math {

    Matrix3::Matrix3()
    {
        memset(m_, 0, sizeof(m_));
    }

    Matrix3::Matrix3(double e11, double e12, double e13, double e21, double e22,
                     double e23, double e31, double e32, double e33)
    {
        m_[0][0] = e11;
        m_[0][1] = e12;
        m_[0][2] = e13;
        m_[1][0] = e21;
        m_[1][1] = e22;
        m_[1][2] = e23;
        m_[2][0] = e31;
        m_[2][1] = e32;
        m_[2][2] = e33;
    }

    Matrix3::~Matrix3()
    {
    }

    Matrix3::Matrix3(const DCM &d)
    {
        *this = d.toMatrix3();
    }

    bool Matrix3::operator==(const Matrix3 &M) const
    {
        return 0 == memcmp(this, &M, sizeof(*this));
    }

    Matrix3 Matrix3::operator+(double f) const
    {
        return Matrix3(m_[0][0] + f, m_[0][1] + f, m_[0][2] + f, m_[1][0] + f,
                       m_[1][1] + f, m_[1][2] + f, m_[2][0] + f, m_[2][1] + f,
                       m_[2][2] + f);
    }

    Matrix3 Matrix3::operator-(double f) const
    {
        return Matrix3(m_[0][0] - f, m_[0][1] - f, m_[0][2] - f, m_[1][0] - f,
                       m_[1][1] - f, m_[1][2] - f, m_[2][0] - f, m_[2][1] - f,
                       m_[2][2] - f);
    }

    Matrix3 Matrix3::operator*(double f) const
    {
        return Matrix3(m_[0][0] * f, m_[0][1] * f, m_[0][2] * f, m_[1][0] * f,
                       m_[1][1] * f, m_[1][2] * f, m_[2][0] * f, m_[2][1] * f,
                       m_[2][2] * f);
    }

    Matrix3 Matrix3::operator/(double f) const
    {
        assert(f != 0);
        return Matrix3(m_[0][0] / f, m_[0][1] / f, m_[0][2] / f, m_[1][0] / f,
                       m_[1][1] / f, m_[1][2] / f, m_[2][0] / f, m_[2][1] / f,
                       m_[2][2] / f);
    }

    Matrix3 &Matrix3::operator+=(double f)
    {
        m_[0][0] += f;
        m_[0][1] += f;
        m_[0][2] += f;
        m_[1][0] += f;
        m_[1][1] += f;
        m_[1][2] += f;
        m_[2][0] += f;
        m_[2][1] += f;
        m_[2][2] += f;

        return *this;
    }

    Matrix3 &Matrix3::operator-=(double f)
    {
        m_[0][0] -= f;
        m_[0][1] -= f;
        m_[0][2] -= f;
        m_[1][0] -= f;
        m_[1][1] -= f;
        m_[1][2] -= f;
        m_[2][0] -= f;
        m_[2][1] -= f;
        m_[2][2] -= f;

        return *this;
    }

    Matrix3 &Matrix3::operator*=(double f)
    {
        m_[0][0] *= f;
        m_[0][1] *= f;
        m_[0][2] *= f;
        m_[1][0] *= f;
        m_[1][1] *= f;
        m_[1][2] *= f;
        m_[2][0] *= f;
        m_[2][1] *= f;
        m_[2][2] *= f;

        return *this;
    }

    Matrix3 &Matrix3::operator/=(double f)
    {
        assert(f != 0);
        m_[0][0] /= f;
        m_[0][1] /= f;
        m_[0][2] /= f;
        m_[1][0] /= f;
        m_[1][1] /= f;
        m_[1][2] /= f;
        m_[2][0] /= f;
        m_[2][1] /= f;
        m_[2][2] /= f;

        return *this;
    }

    Matrix3 Matrix3::operator+(const Matrix3 &B) const
    {
        return Matrix3(
            m_[0][0] + B(1, 1), m_[0][1] + B(1, 2), m_[0][2] + B(1, 3),
            m_[1][0] + B(2, 1), m_[1][1] + B(2, 2), m_[1][2] + B(2, 3),
            m_[2][0] + B(3, 1), m_[2][1] + B(3, 2), m_[2][2] + B(3, 3));
    }

    Matrix3 Matrix3::operator-(const Matrix3 &B) const
    {
        return Matrix3(
            m_[0][0] - B(1, 1), m_[0][1] - B(1, 2), m_[0][2] - B(1, 3),
            m_[1][0] - B(2, 1), m_[1][1] - B(2, 2), m_[1][2] - B(2, 3),
            m_[2][0] - B(3, 1), m_[2][1] - B(3, 2), m_[2][2] - B(3, 3));
    }

    Matrix3 &Matrix3::operator+=(const Matrix3 &B)
    {
        m_[0][0] += B(1, 1);
        m_[0][1] += B(1, 2);
        m_[0][2] += B(1, 3);
        m_[1][0] += B(2, 1);
        m_[1][1] += B(2, 2);
        m_[1][2] += B(2, 3);
        m_[2][0] += B(3, 1);
        m_[2][1] += B(3, 2);
        m_[2][2] += B(3, 3);

        return *this;
    }

    Matrix3 &Matrix3::operator-=(const Matrix3 &B)
    {
        m_[0][0] -= B(1, 1);
        m_[0][1] -= B(1, 2);
        m_[0][2] -= B(1, 3);
        m_[1][0] -= B(2, 1);
        m_[1][1] -= B(2, 2);
        m_[1][2] -= B(2, 3);
        m_[2][0] -= B(3, 1);
        m_[2][1] -= B(3, 2);
        m_[2][2] -= B(3, 3);

        return *this;
    }

    Matrix3 Matrix3::operator*(const Matrix3 &B) const
    {
        return Matrix3(
            m_[0][0] * B(1, 1) + m_[0][1] * B(2, 1) + m_[0][2] * B(3, 1),
            m_[0][0] * B(1, 2) + m_[0][1] * B(2, 2) + m_[0][2] * B(3, 2),
            m_[0][0] * B(1, 3) + m_[0][1] * B(2, 3) + m_[0][2] * B(3, 3),
            m_[1][0] * B(1, 1) + m_[1][1] * B(2, 1) + m_[1][2] * B(3, 1),
            m_[1][0] * B(1, 2) + m_[1][1] * B(2, 2) + m_[1][2] * B(3, 2),
            m_[1][0] * B(1, 3) + m_[1][1] * B(2, 3) + m_[1][2] * B(3, 3),
            m_[2][0] * B(1, 1) + m_[2][1] * B(2, 1) + m_[2][2] * B(3, 1),
            m_[2][0] * B(1, 2) + m_[2][1] * B(2, 2) + m_[2][2] * B(3, 2),
            m_[2][0] * B(1, 3) + m_[2][1] * B(2, 3) + m_[2][2] * B(3, 3));
    }

    Matrix3 &Matrix3::operator*=(const Matrix3 &B)
    {
        return *this = *this * B;
    }

    math::Vec3<> Matrix3::operator*(const Vec3<> &v) const
    {
        return Vec3<>(m_[0][0] * v(1) + m_[0][1] * v(2) + m_[0][2] * v(3),
                      m_[1][0] * v(1) + m_[1][1] * v(2) + m_[1][2] * v(3),
                      m_[2][0] * v(1) + m_[2][1] * v(2) + m_[2][2] * v(3));
    }

    Matrix3 Matrix3::transpose() const
    {
        return Matrix3(m_[0][0], m_[1][0], m_[2][0], m_[0][1], m_[1][1],
                       m_[2][1], m_[0][2], m_[1][2], m_[2][2]);
    }

    Matrix3 Matrix3::inverse() const
    {
        double determinant = this->determinant();

        /* A singular matrix cannot be inverted.
         */
        assert(determinant != 0);

        /*
           | a b c |
           | d e f |
           | g h k |
         */
        return Matrix3(
                   // A = ek - fh
                   m_[1][1] * m_[2][2] - m_[1][2] * m_[2][1],
                   // B = ch - bk
                   m_[0][2] * m_[2][1] - m_[0][1] * m_[2][2],
                   // C = bf - ce
                   m_[0][1] * m_[1][2] - m_[0][2] * m_[1][1],
                   // D = fg - dk
                   m_[1][2] * m_[2][0] - m_[1][0] * m_[2][2],
                   // E = ak - cg
                   m_[0][0] * m_[2][2] - m_[0][2] * m_[2][0],
                   // F = cd - af
                   m_[0][2] * m_[1][0] - m_[0][0] * m_[1][2],
                   // G = dh - eg
                   m_[1][0] * m_[2][1] - m_[1][1] * m_[2][0],
                   // H = bg - ah
                   m_[0][1] * m_[2][0] - m_[0][0] * m_[2][1],
                   // K = ae - bd
                   m_[0][0] * m_[1][1] - m_[0][1] * m_[1][0]) /
               determinant;
    }

    double Matrix3::determinant() const
    {
        return m_[0][0] * m_[1][1] * m_[2][2] + m_[0][1] * m_[1][2] * m_[2][0] +
               m_[0][2] * m_[1][0] * m_[2][1] - m_[0][0] * m_[1][2] * m_[2][1] -
               m_[0][1] * m_[1][0] * m_[2][2] - m_[0][2] * m_[1][1] * m_[2][0];
        return 0;
    }

    double Matrix3::trace() const
    {
        return m_[0][0] + m_[1][1] + m_[2][2];
    }

    double det(const Matrix3 &M)
    {
        return M.determinant();
    }

} // namespace
