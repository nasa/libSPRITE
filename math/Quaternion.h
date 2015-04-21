#ifndef __MATH_QUATERNION_H__
#define __MATH_QUATERNION_H__

#include "math/Vec3.h"

/**
 * Forward Declartion of units.
 */
namespace units
{
    class Radians;
} // namespace

namespace math
{

    /**
     * Forward declartion of classes.
     */
    class Euler;
    class DCM;

    class Quaternion
    {
      public:
        /**
         * Default contructor.
         * This constructor creates a quaternion with identity values.
         */
        Quaternion()
            : m_w(1)
            , m_v(0, 0, 0)
        {
        }

        /**
         * Construct a quaternion from scalar and vector components.
         */
        Quaternion(double s, const Vec3<> &v);

#if 0
            /**
             * Construct a quaternion from a unit vector and and angle.
             */
            Quaternion(const Vec3& rotation_vector,
                    const units::Radians rotation_angle);
#endif

        /**
         * Convert an Euler angle to a quaternion.
         */
        explicit Quaternion(const Euler &e);

        /**
         * Convert a direction cosine matrix to a quaternion.
         */
        explicit Quaternion(const DCM &dcm);

        /**
         * Get the scalar part of the quaternion.
         * @return Scalar portion of the quaternion.
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
         */
        double &scaler()
        {
            return m_w;
        }

        /**
         * Get the vector part of the quaternion.
         * @return The vector portion of the quaternion.
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
         */
        Vec3<> &vector()
        {
            return m_v;
        }

        /**
         * Get an element of the vector part of the quaternion.
         * @return The vector element value.
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
         */
        double &vector(unsigned int i)
        {
            return m_v(i);
        }

        /**
         * Produce the product of two quaternions.
         * @param rhs Quaternion to mutiply by.
         * @return Return the product of the two quaternions Q = q * rhs;
         */
        Quaternion operator*(const Quaternion &rhs) const;

        /**
         * Assign the product of two quaternions to this class.
         * @param rhs Quaternion to mutiply by.
         * @return Return this class after multiplication. Q *= rhs;
         */
        Quaternion &operator*=(const Quaternion &rhs);

        /**
         * Perform a vector rotation.
         * @param v Vector to be rotated.
         * @return The rotated vector.
         */
        Vec3<> operator*(const Vec3<> &v) const;

        /**
         * Return the conjugate of the quaternion.
         * @return A new quaternion representing the conjugate of this
         * quaternion.
         */
        Quaternion conjugate() const;

        /**
         * Return the inverse of the quaternion.
         * @return A new quaternion representing the inverse of this
         * quaternion.
         */
        Quaternion inverse() const;

        /**
         * Convert a quaternion to euler angles.
         * @return The equivelant euler angles.
         */
        Euler toEuler() const;

        /**
         * Convert a quaternion to a direction cosine matrix.
         * @return The equivelant direction cosine matrix.
         */
        DCM toDCM() const;

        /**
         * Normalize the quaternion.
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
