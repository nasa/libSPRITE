// $Id$

#ifndef __MATH_DCM_H__
#define __MATH_DCM_H__

#include "Vec3.h"
#include "Matrix3.h"

namespace math
{

    /**
     * Forward declaration of class.
     */
    class Euler;
    class Quaternion;

    /**
     * Direction Cosine Matrix (DCM)
     * A direction cosine matrix is a specialized form of a 3x3 matrix.
     */
    class DCM : private Matrix3
    {

        public:

            /**
             * Constructor with initial values.
             */
            DCM(double e11, double e12, double e13,
                    double e21, double e22, double e23,
                    double e31, double e32, double e33) :
                Matrix3(e11, e12, e13, e21, e22, e23, e31, e32, e33)
        {
        }

            /**
             * Construct a DCM from a 3x3 matrix
             * @param m initial matrix
             */
            explicit DCM(const Matrix3& m) :
                Matrix3(m)
        {
        }

            /**
             * Construct a DCM from Euler angles.
             */
            explicit DCM(const Euler& e);


            /**
             * Access elements of the matrix.
             */
            using Matrix3::operator();
            /**
             * Vector muliplication.
             * @return A new vector with the value V' = M * v
             */
            using Matrix3::operator*;

            /**
             * DCM transpose.
             * @return A new matrix with the elements transposed.
             */
            DCM transpose() const
            {
                return static_cast<DCM>(this->Matrix3::transpose());
            }

            /**
             * DCM inverse.
             * @return A new matrix that is the inverse of the current matrix.
             */
            DCM inverse() const
            {
                /* The inverse and transpose of a DCM are equivelent.
                 */
                return DCM(transpose());
            }

            /**
             * Convert the DCM to a 3x3 matrix.
             * @return 3x3 matrix
             */
            Matrix3 toMatrix3() const
            {
                return *this;
            }

            /**
             * Convert the DCM to euler angles.
             * @return The equivelent euler angles.
             */
            Euler toEuler() const;

            /**
             * Convert the DCM to a quaternion.
             * @return The equivelent quaternion
             */
            Quaternion toQuaternion() const;

    };

} // namespace

#endif // __MATH_DCM_H__
