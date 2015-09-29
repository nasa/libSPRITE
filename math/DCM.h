#ifndef __MATH_DCM_H__
#define __MATH_DCM_H__

#include "math/Vec3.h"
#include "math/Matrix3.h"

namespace math {

    /**
     * Forward declaration of class.
     */
    class Euler;
    class Quaternion;

    /**
     * Direction Cosine Matrix (DCM)
     * A direction cosine matrix is a specialized form of a 3x3 matrix.
     */
    class DCM : private Matrix3 {

      public:
        /**
         * Default contructor
         * @satisfies{math-7.1}
         */
        DCM() : Matrix3()
        {
        }

        /**
         * Constructor with initial values.
         * @satisfies{math-7.2}
         */
        DCM(double e11, double e12, double e13, double e21, double e22,
            double e23, double e31, double e32, double e33)
            : Matrix3(e11, e12, e13, e21, e22, e23, e31, e32, e33)
        {
        }

        /**
         * Construct a DCM from a 3x3 matrix
         * @param m initial matrix
         * @satisfies{math-7.4}
         */
        explicit DCM(const Matrix3 &m) : Matrix3(m)
        {
        }

        /**
         * Construct a DCM from Euler angles.
         * @satisfies{math-7.5}
         */
        explicit DCM(const Euler &e);

        /**
         * Access elements of the matrix.
         * @satisfies{math-7.3}
         */
        using Matrix3::operator();

        /**
         * Vector muliplication.
         * @return A new vector with the value V' = M * v
         * @satisfies{math-7.9}
         */
        using Matrix3::operator*;

        /**
         * DCM transpose.
         * @return A new matrix with the elements transposed.
         * @satisfies{math-7.10}
         */
        DCM transpose() const
        {
            return static_cast<DCM>(this->Matrix3::transpose());
        }

        /**
         * DCM inverse.
         * @return A new matrix that is the inverse of the current matrix.
         * @satisfies{math-7.11}
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
         * @satisfies{math-7.6}
         */
        Matrix3 toMatrix3() const
        {
            return *this;
        }

        /**
         * Convert the DCM to euler angles.
         * @return The equivelent euler angles.
         * @satisfies{math-7.7}
         */
        Euler toEuler() const;

        /**
         * Convert the DCM to a quaternion.
         * @return The equivelent quaternion
         * @satisfies{math-7.8}
         */
        Quaternion toQuaternion() const;
    };

} // namespace

#endif // __MATH_DCM_H__
