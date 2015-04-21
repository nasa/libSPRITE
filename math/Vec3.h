#ifndef __MATH_VEC3_H__
#define __MATH_VEC3_H__

#include "base/assertion.h"
#include "base/types.h"
#include <math.h>

namespace math
{

    /**
     * This class manages the common case of three element vectors.
     */
    template <typename T = double> class Vec3
    {
      public:
        /**
         * Default constructor.
         */
        Vec3()
        {
            m_[0] = T(0);
            m_[1] = T(0);
            m_[2] = T(0);
        }

        /**
         * Constructor
         * @param xx Initial value for X.
         * @param xx Initial value for Y.
         * @param xx Initial value for Z.
         */
        Vec3(T xx, T yy, T zz)
        {
            m_[0] = xx;
            m_[1] = yy;
            m_[2] = zz;
        }

        /**
         * Constructor
         * @param xx Initial value for X.
         * @param xx Initial value for Y.
         * @param xx Initial value for Z.
         */
        Vec3(double xx, double yy, double zz)
        {
            m_[0] = T(xx);
            m_[1] = T(yy);
            m_[2] = T(zz);
        }

        /**
         * Operator overload for accessing an element.
         * Used like this: double x = V(i);
         * @param i Element to access.
         * @return Eelement value.
         */
        T operator()(unsigned int i) const
        {
            assert((i >= 1) && (i <= 3));

            return m_[i - 1];
        }

        /**
         * Operator overload for settting an element.
         * Used like this: V(i) = 3.14;
         * @param i Element to access.
         * @return Reference to the element.
         */
        T &operator()(unsigned int i)
        {
            assert((i >= 1) && (i <= 3));

            return m_[i - 1];
        }

        /**
         * Scalar addition.
         * @param f Scalar to add to the right of vector
         * @return New vector V1 = V + f
         */
        Vec3<T> operator+(double f) const
        {
            return Vec3<T>(m_[0] + f, m_[1] + f, m_[2] + f);
        }

        /**
         * Scalar subtraction.
         * @param f Scalar to subtract from the right of vector
         * @return New vector V1 = V - f
         */
        Vec3<T> operator-(double f) const
        {
            return Vec3<T>(m_[0] - f, m_[1] - f, m_[2] - f);
        }

        /**
         * Scalar multiplication.
         * @param f Scalar to multiply to the right of vector
         * @return New vector V1 = V * f
         */
        Vec3<T> operator*(double f) const
        {
            return Vec3<T>(m_[0] * f, m_[1] * f, m_[2] * f);
        }

        /**
         * Scalar divide.
         * @param f Scalar to divide from the vector
         * @return New vector V1 = V / f
         */
        Vec3<T> operator/(double f) const
        {
            assert(f != 0);
            return Vec3<T>(m_[0] / f, m_[1] / f, m_[2] / f);
        }

        /**
         * Scalar addition.
         * @param f Scalar to add to the vector
         */
        Vec3<T> &operator+=(double f)
        {
            return *this = *this + f;
        }

        /**
         * Scalar subtraction.
         * @param f Scalar to subtract from the vector
         */
        Vec3<T> &operator-=(double f)
        {
            return *this = *this - f;
        }

        /**
         * Scalar multiplication.
         * @param f Scalar to multiply to the vector
         */
        Vec3<T> &operator*=(double f)
        {
            return *this = *this * f;
        }

        /**
         * Scalar divide.
         * @param f Scalar to divide from the vector
         */
        Vec3<T> &operator/=(double f)
        {
            return *this = *this / f;
        }

        /**
         * Vector addition.
         * @param v Vector to add to the right
         * @return new vector V1 = V + v
         */
        Vec3<T> operator+(const Vec3<T> &v) const
        {
            return Vec3<T>(T(m_[0] + v.m_[0]), T(m_[1] + v.m_[1]),
                           T(m_[2] + v.m_[2]));
        }

        /**
         * Vector subtraction.
         * @param v Vector to subtract from the right
         * @return new vector V1 = V - v
         */
        Vec3<T> operator-(const Vec3<T> &v) const
        {
            return Vec3<T>(T(m_[0] - v.m_[0]), T(m_[1] - v.m_[1]),
                           T(m_[2] - v.m_[2]));
        }

        /**
         * Vector addition.
         * @param v Vector to add
         */
        Vec3<T> &operator+=(const Vec3<T> &v)
        {
            return *this = *this + v;
        }

        /**
         * Vector subtraction.
         * @param v Vector to subtract
         */
        Vec3<T> &operator-=(const Vec3<T> &v)
        {
            return *this = *this - v;
        }

        /**
         * Calculate the vector magnited squared.
         * @return Magnitude^2
         */
        double magnitude_squared() const
        {
            return m_[0] * m_[0] + m_[1] * m_[1] + m_[2] * m_[2];
        }

        /**
         * Calculate the vector magnitude.
         * @return Vector magnitude.
         */
        double magnitude() const
        {
            return sqrt(magnitude_squared());
        }

        void normalize()
        {
            double m = magnitude();
            *this = *this / m;
        }

        /**
         * Calculate the dot product.
         * @param v = Vector on the right
         * @return Scalar result of V * v
         */
        double dot(const Vec3<T> &v) const
        {
            return m_[0] * v.m_[0] + m_[1] * v.m_[1] + m_[2] * v.m_[2];
        }

      protected:
        T m_[3];
    };

    /**
     * Specialized template class for the case where the type stored is a
     * double.
     */
    template <> class Vec3<double>
    {
      public:
        /**
         * Default constructor.
         */
        Vec3()
        {
            m_[0] = 0;
            m_[1] = 0;
            m_[2] = 0;
        }

        /**
         * Constructor
         * @param xx Initial value for X.
         * @param xx Initial value for Y.
         * @param xx Initial value for Z.
         */
        Vec3(double xx, double yy, double zz)
        {
            m_[0] = (fabs(xx) > NEAR_ZERO) ? xx : 0;
            m_[1] = (fabs(yy) > NEAR_ZERO) ? yy : 0;
            m_[2] = (fabs(zz) > NEAR_ZERO) ? zz : 0;
        }

        /**
         * Operator overload for accessing an element.
         * Used like this: double x = V(i);
         * @param i Element to access.
         * @return Eelement value.
         */
        double operator()(unsigned int i) const
        {
            assert((i >= 1) && (i <= 3));

            return m_[i - 1];
        }

        /**
         * Operator overload for settting an element.
         * Used like this: V(i) = 3.14;
         * @param i Element to access.
         * @return Reference to the element.
         */
        double &operator()(unsigned int i)
        {
            assert((i >= 1) && (i <= 3));

            return m_[i - 1];
        }

        /**
         * Scalar addition.
         * @param f Scalar to add to the right of vector
         * @return New vector V1 = V + f
         */
        Vec3<double> operator+(double f) const
        {
            return Vec3<double>(m_[0] + f, m_[1] + f, m_[2] + f);
        }

        /**
         * Scalar subtraction.
         * @param f Scalar to subtract from the right of vector
         * @return New vector V1 = V - f
         */
        Vec3<double> operator-(double f) const
        {
            return Vec3<double>(m_[0] - f, m_[1] - f, m_[2] - f);
        }

        /**
         * Scalar multiplication.
         * @param f Scalar to multiply to the right of vector
         * @return New vector V1 = V * f
         */
        Vec3<double> operator*(double f) const
        {
            return Vec3<double>(m_[0] * f, m_[1] * f, m_[2] * f);
        }

        /**
         * Scalar divide.
         * @param f Scalar to divide from the vector
         * @return New vector V1 = V / f
         */
        Vec3<double> operator/(double f) const
        {
            assert(f != 0);
            return Vec3<double>(m_[0] / f, m_[1] / f, m_[2] / f);
        }

        /**
         * Scalar addition.
         * @param f Scalar to add to the vector
         */
        Vec3<double> &operator+=(double f)
        {
            return *this = *this + f;
        }

        /**
         * Scalar subtraction.
         * @param f Scalar to subtract from the vector
         */
        Vec3<double> &operator-=(double f)
        {
            return *this = *this - f;
        }

        /**
         * Scalar multiplication.
         * @param f Scalar to multiply to the vector
         */
        Vec3<double> &operator*=(double f)
        {
            return *this = *this * f;
        }

        /**
         * Scalar divide.
         * @param f Scalar to divide from the vector
         */
        Vec3<double> &operator/=(double f)
        {
            return *this = *this / f;
        }

        /**
         * Vector addition.
         * @param v Vector to add to the right
         * @return new vector V1 = V + v
         */
        Vec3<double> operator+(const Vec3<double> &v) const
        {
            return Vec3<double>(m_[0] + v.m_[0], m_[1] + v.m_[1],
                                m_[2] + v.m_[2]);
        }

        /**
         * Vector subtraction.
         * @param v Vector to subtract from the right
         * @return new vector V1 = V - v
         */
        Vec3<double> operator-(const Vec3<double> &v) const
        {
            return Vec3<double>(m_[0] - v.m_[0], m_[1] - v.m_[1],
                                m_[2] - v.m_[2]);
        }

        /**
         * Vector addition.
         * @param v Vector to add
         */
        Vec3<double> &operator+=(const Vec3<double> &v)
        {
            return *this = *this + v;
        }

        /**
         * Vector subtraction.
         * @param v Vector to subtract
         */
        Vec3<double> &operator-=(const Vec3<double> &v)
        {
            return *this = *this - v;
        }

        /**
         * Calculate the vector magnited squared.
         * @return Magnitude^2
         */
        double magnitude_squared() const
        {
            return m_[0] * m_[0] + m_[1] * m_[1] + m_[2] * m_[2];
        }

        /**
         * Calculate the vector magnitude.
         * @return Vector magnitude.
         */
        double magnitude() const
        {
            return sqrt(magnitude_squared());
        }

        void normalize()
        {
            double m = magnitude();
            *this = *this / m;
        }

        /**
         * Calculate the dot product.
         * @param v = Vector on the right
         * @return Scalar result of V * v
         */
        double dot(const Vec3<double> &v) const
        {
            return m_[0] * v.m_[0] + m_[1] * v.m_[1] + m_[2] * v.m_[2];
        }

      protected:
        double m_[3];
    };

    Vec3<> cross(const Vec3<> &v1, const Vec3<> &v2);

} // namespace

#endif // __MATH_VEC3_H__
