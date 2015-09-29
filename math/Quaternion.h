#ifndef __MATH_QUATERNION_H__
#define __MATH_QUATERNION_H__

#include "math/Vec3.h"

namespace math {

    /**
     * Forward declartion of classes.
     */
    class Euler;
    class DCM;

    class Quaternion {
      public:
        /**
         * Default contructor.
         * This constructor creates a quaternion with identity values.
         * @satisfies{math-6.1}
         */
        Quaternion()
            : m_w(1)
            , m_v(0, 0, 0)
        {
        }

        /**
         * Construct a quaternion from scalar and vector components.
         * @satisfies{math-6.2}
         */
        Quaternion(double s, const Vec3<> &v);

        /**
         * Convert an Euler angle to a quaternion.
         * @satisfies{math-6.3}
         */
        explicit Quaternion(const Euler &e);

        /**
         * Convert a direction cosine matrix to a quaternion.
         * @satisfies{math-6.4}
         */
        explicit Quaternion(const DCM &dcm);

        /**
         * Get the scalar part of the quaternion.
         * @return Scalar portion of the quaternion.
         * @satisfies{math-6.5}
         */
        double scalar() const
        {
            return m_w;
        }

        /**
         * Get access to the scalar part of the quaternion.
         * This function can be used to directly modify the scalar part of
         * a quaternion. For example q.scalar() = 0.14.
         * @return A reference to the scalar portion of the quaternion.
         * @warning Be sure to normalize quaternions after directly
         * modifying thier values.
         * @satisfies{math-6.5}
         */
        double &scaler()
        {
            return m_w;
        }

        /**
         * Get the vector part of the quaternion.
         * @return The vector portion of the quaternion.
         * @satisfies{math-6.7}
         */
        Vec3<> vector() const
        {
            return m_v;
        }

        /**
         * Get access to the vector part of the quaternion.
         * @return A reference to the vector portion of the quaternion.
         * @warning Be sure to normalize quaternions after directly
         * modifying thier values.
         * @satisfies{math-6.8}
         */
        Vec3<> &vector()
        {
            return m_v;
        }

        /**
         * Get an element of the vector part of the quaternion.
         * @return The vector element value.
         * @satisfies{math-6.9}
         */
        double vector(unsigned int i) const
        {
            return m_v(i);
        }

        /**
         * Get access to an element of the vector part of the quaternion.
         * This function can be used to directly modify a vector element.
         * For example q.vector(1) = 0.14.
         * @return A reference to the vector element.
         * @warning Be sure to normalize quaternions after directly
         * modifying thier values.
         * @satisfies{math-6.10}
         */
        double &vector(unsigned int i)
        {
            return m_v(i);
        }

        /**
         * Produce the product of two quaternions.
         * @param rhs Quaternion to mutiply by.
         * @return Return the product of the two quaternions Q = q * rhs;
         * @satisfies{math-6.11}
         */
        Quaternion operator*(const Quaternion &rhs) const;

        /**
         * Assign the product of two quaternions to this class.
         * @param rhs Quaternion to mutiply by.
         * @return Return this class after multiplication. Q *= rhs;
         * @satisfies{math-6.12}
         */
        Quaternion &operator*=(const Quaternion &rhs);

        /**
         * Perform a vector rotation.
         * @param v Vector to be rotated.
         * @return The rotated vector.
         * @satisfies{math-6.13}
         */
        Vec3<> operator*(const Vec3<> &v) const;

        /**
         * Return the conjugate of the quaternion.
         * @return A new quaternion representing the conjugate of this
         * quaternion.
         * @satisfies{math-6.14}
         */
        Quaternion conjugate() const;

        /**
         * Return the inverse of the quaternion.
         * @return A new quaternion representing the inverse of this
         * quaternion.
         * @satisfies{math-6.15}
         */
        Quaternion inverse() const;

        /**
         * Convert a quaternion to euler angles.
         * @return The equivelant euler angles.
         * @satisfies{math-6.16}
         */
        Euler toEuler() const;

        /**
         * Convert a quaternion to a direction cosine matrix.
         * @return The equivelant direction cosine matrix.
         * @satisfies{math-6.17}
         */
        DCM toDCM() const;

        /**
         * Normalize the quaternion.
         * @satisfies{math-6.18}
         */
        void normalize();

      private:
        /**
         * Scalar portion of the quaternion.
         */
        double m_w;

        /**
         * Vector portion of the quaternion.
         */
        Vec3<> m_v;
    };

} // namespace

#endif // __MATH_QUATERNION_H__
