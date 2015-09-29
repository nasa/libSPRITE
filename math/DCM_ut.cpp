#include <math.h>
#include "math/DCM.h"
#include "math/DCM_ut.h"
#include "math/Euler.h"

namespace math {

    void DCM_ut::setUp()
    {
    }

    void DCM_ut::tearDown()
    {
    }

    void DCM_ut::test_DCM()
    {
        double epsilon = .0001;
        const units::Radians roll = units::Radians(2);
        const units::Radians pitch = units::Radians(1.5);
        const units::Radians yaw = units::Radians(1);

        const DCM d(Euler(roll, pitch, yaw));
        const Matrix3 m = d.toMatrix3();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0382, m(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0595, m(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.9975, m(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.8402, m(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5384, m(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0643, m(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5409, m(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.8406, m(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.0294, m(3, 3), epsilon);

        /* The rows and columns should be unit vectors.
         */
        epsilon = 1e-12;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 1), 2) + pow(m(1, 2), 2) + pow(m(1, 3), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(2, 1), 2) + pow(m(2, 2), 2) + pow(m(2, 3), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(3, 1), 2) + pow(m(3, 2), 2) + pow(m(3, 3), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 1), 2) + pow(m(2, 1), 2) + pow(m(3, 1), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 2), 2) + pow(m(2, 2), 2) + pow(m(3, 2), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 3), 2) + pow(m(2, 3), 2) + pow(m(3, 3), 2), epsilon);
    }

    void DCM_ut::test_Euler_to_DCM()
    {
        const units::Radians roll = units::Radians(2);
        const units::Radians pitch = units::Radians(1.5);
        const units::Radians yaw = units::Radians(1);

        const Euler e(roll, pitch, yaw);
        const DCM d1 = e.toDCM();
        const DCM d2 = DCM(e);

        CPPUNIT_ASSERT(Matrix3(d1) == Matrix3(d2));
    }

    void DCM_ut::test_multiply_vector()
    {
        const double epsilon = .0001;
        const DCM d(
            Euler(units::Radians(6), units::Radians(3), units::Radians(1)));
        const Vec3<> v(1, 2, 3);

        const Vec3<> r = d * v;

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.6244, r(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.9718, r(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-2.4836, r(3), epsilon);
    }

    void DCM_ut::test_transpose()
    {
        double epsilon = .0001;
        const DCM d(
            Euler(units::Radians(6), units::Radians(3), units::Radians(1)));
        const Matrix3 m = Matrix3(d.transpose());

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.5349, m(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.8293, m(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1619, m(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.8330, m(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4856, m(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2650, m(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1411, m(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2766, m(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.9506, m(3, 3), epsilon);

        /* The rows and columns should be unit vectors.
         */
        epsilon = 1e-12;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 1), 2) + pow(m(1, 2), 2) + pow(m(1, 3), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(2, 1), 2) + pow(m(2, 2), 2) + pow(m(2, 3), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(3, 1), 2) + pow(m(3, 2), 2) + pow(m(3, 3), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 1), 2) + pow(m(2, 1), 2) + pow(m(3, 1), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 2), 2) + pow(m(2, 2), 2) + pow(m(3, 2), 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(
            1.0, pow(m(1, 3), 2) + pow(m(2, 3), 2) + pow(m(3, 3), 2), epsilon);
    }

    void DCM_ut::test_inverse()
    {
        const DCM d(
            Euler(units::Radians(6), units::Radians(3), units::Radians(1)));
        const DCM dt = d.transpose();
        const DCM di = d.inverse();

        /* The transpose and inverse should be identical.
         */
        CPPUNIT_ASSERT(Matrix3(dt) == Matrix3(di));
    }

} // namespace
