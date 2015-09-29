#ifndef __MATH_VEC3_H__
#define __MATH_VEC3_H__

#include "base/assertion.h"
#include "base/types.h"
#include <math.h>

namespace math {

    /**
     * This class manages the common case of three element vectors.
     */
    template <typename T = double> class Vec3 {
      public:
        /**
         * Constructor
         * @param xx Initial value for X.
         * @param xx Initial value for Y.
         * @param xx Initial value for Z.
         * @satisfies{math-4.1}
         * @satisfies{math-4.2}
         */
        Vec3(T xx = 0, T yy = 0, T zz = 0)
        {
            m_[0] = xx;
            m_[1] = yy;
            m_[2] = zz;
        }

        /**
         * Operator overload for accessing an element.
         * Used like this: double x = V(i);
         * @param i Element to access.
         * @return Eelement value.
         * @satisfies{math-4.3}
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
         * @satisfies{math-4.3}
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
         * @satisfies{math-4.4}
         */
        Vec3<T> operator+(double f) const
        {
            return Vec3<T>(m_[0] + f, m_[1] + f, m_[2] + f);
        }

        /**
         * Scalar subtraction.
         * @param f Scalar to subtract from the right of vector
         * @return New vector V1 = V - f
         * @satisfies{math-4.4}
         */
        Vec3<T> operator-(double f) const
        {
            return Vec3<T>(m_[0] - f, m_[1] - f, m_[2] - f);
        }

        /**
         * Scalar multiplication.
         * @param f Scalar to multiply to the right of vector
         * @return New vector V1 = V * f
         * @satisfies{math-4.4}
         */
        Vec3<T> operator*(double f) const
        {
            return Vec3<T>(m_[0] * f, m_[1] * f, m_[2] * f);
        }

        /**
         * Scalar divide.
         * @param f Scalar to divide from the vector
         * @return New vector V1 = V / f
         * @satisfies{math-4.4}
         */
        Vec3<T> operator/(double f) const
        {
            assert(f != 0);
            return Vec3<T>(m_[0] / f, m_[1] / f, m_[2] / f);
        }

        /**
         * Scalar addition.
         * @param f Scalar to add to the vector
         * @satisfies{math-4.4}
         */
        Vec3<T> &operator+=(double f)
        {
            return *this = *this + f;
        }

        /**
         * Scalar subtraction.
         * @param f Scalar to subtract from the vector
         * @satisfies{math-4.4}
         */
        Vec3<T> &operator-=(double f)
        {
            return *this = *this - f;
        }

        /**
         * Scalar multiplication.
         * @param f Scalar to multiply to the vector
         * @satisfies{math-4.4}
         */
        Vec3<T> &operator*=(double f)
        {
            return *this = *this * f;
        }

        /**
         * Scalar divide.
         * @param f Scalar to divide from the vector
         * @satisfies{math-4.4}
         */
        Vec3<T> &operator/=(double f)
        {
            return *this = *this / f;
        }

        /**
         * Vector addition.
         * @param v Vector to add to the right
         * @return new vector V1 = V + v
         * @satisfies{math-4.5}
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
         * @satisfies{math-4.5}
         */
        Vec3<T> operator-(const Vec3<T> &v) const
        {
            return Vec3<T>(T(m_[0] - v.m_[0]), T(m_[1] - v.m_[1]),
                           T(m_[2] - v.m_[2]));
        }

        /**
         * Vector addition.
         * @param v Vector to add
         * @satisfies{math-4.5}
         */
        Vec3<T> &operator+=(const Vec3<T> &v)
        {
            return *this = *this + v;
        }

        /**
         * Vector subtraction.
         * @param v Vector to subtract
         * @satisfies{math-4.5}
         */
        Vec3<T> &operator-=(const Vec3<T> &v)
        {
            return *this = *this - v;
        }

        /**
         * Calculate the vector magnitude squared.
         * @return Magnitude^2
         * @satisfies{math-4.7}
         */
        double magnitude_squared() const
        {
            return m_[0] * m_[0] + m_[1] * m_[1] + m_[2] * m_[2];
        }

        /**
         * Calculate the vector magnitude.
         * @return Vector magnitude.
         * @satisfies{math-4.6}
         */
        double magnitude() const
        {
            return sqrt(magnitude_squared());
        }

        /**
         * Normalize the vector to have a magintude of 1.
         * @satisfies{math-4.8}
         */
        void normalize()
        {
            double m = magnitude();
            *this = *this / m;
        }

        /**
         * Calculate the dot product.
         * @param v = Vector on the right
         * @return Scalar result of V * v
         * @satisfies{math-4.9}
         */
        double dot(const Vec3<T> &v) const
        {
            return m_[0] * v.m_[0] + m_[1] * v.m_[1] + m_[2] * v.m_[2];
        }

      protected:
        T m_[3];
    };

    /**
     * Compute the cross product of two vectors.
     * @param v1 First vector.
     * @param v2 Second vector.
     * @retrurn Cross product of the two vectors.
     * @satisfies{math-4.10}
     */
    Vec3<> cross(const Vec3<> &v1, const Vec3<> &v2);

} // namespace

#endif // __MATH_VEC3_H__
