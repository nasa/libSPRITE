#include <math.h>
#include "math/DCM.h"
#include "math/Quaternion.h"
#include "math/Quaternion_ut.h"
#include "math/Euler.h"

namespace math {

    void Quaternion_ut::setUp()
    {
    }

    void Quaternion_ut::tearDown()
    {
    }

    void Quaternion_ut::test_Quaternion()
    {
        const Quaternion q;

        CPPUNIT_ASSERT_EQUAL(1.0, q.scalar());
        CPPUNIT_ASSERT_EQUAL(0.0, q.vector(1));
        CPPUNIT_ASSERT_EQUAL(0.0, q.vector(2));
        CPPUNIT_ASSERT_EQUAL(0.0, q.vector(3));
    }

    void Quaternion_ut::test_Quaternion_from_scalar_vector()
    {
        const double epsilon = 0.0001;
        Quaternion q(1, Vec3<>(0, 1, 0));

        /* The quaternion should be automatically normalized upon creation.
         */
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.vector(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.vector(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.vector(3), epsilon);

        q = Quaternion(-1, Vec3<>(0, 1, 0));

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.7071, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.vector(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.vector(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.vector(3), epsilon);
    }

#if 0
    void Quaternion_ut::test_Quaternion_from_angle_vector()
    {
        CPPUNIT_ASSERT(false);
    }
#endif

    void Quaternion_ut::test_Quaternion_from_Euler()
    {
        double epsilon = 0.0001;
        units::Radians roll(0);
        units::Radians pitch(0.1);
        units::Radians yaw(0.7845);
        Euler e(roll, pitch, yaw);
        Quaternion q(e);
        Vec3<> v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.9229, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.0191, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0462, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3818, v(3), epsilon);

        epsilon = 1e-12;
        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(yaw, e.get_yaw(), epsilon);

        epsilon = 0.0001;
        roll = units::Radians(M_PI / 2);
        pitch = units::Radians(0);
        yaw = units::Radians(0);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        epsilon = 1e-12;
        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(yaw, e.get_yaw(), epsilon);

        epsilon = 0.0001;
        roll = units::Radians(-M_PI / 2);
        pitch = units::Radians(0);
        yaw = units::Radians(0);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.7071, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        epsilon = 1e-12;
        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(yaw, e.get_yaw(), epsilon);

        epsilon = 0.0001;
        roll = units::Radians(M_PI / 2);
        pitch = units::Radians(-M_PI / 3);
        yaw = units::Radians(M_PI / 6);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6830, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1830, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, v(3), epsilon);

        epsilon = 1e-12;
        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(yaw, e.get_yaw(), epsilon);

        roll = units::Radians(M_PI);
        pitch = units::Radians(0);
        yaw = units::Radians(0);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(yaw, e.get_yaw(), epsilon);

        roll = units::Radians(0);
        pitch = units::Radians(M_PI);
        yaw = units::Radians(0);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        e = Euler(q);
        /* There are equivalent sets of angles that acheive the same
         * orientation. Test for either.
         */
        double d = e.get_pitch();
        if((d < (pitch + epsilon)) && (d > (pitch - epsilon))) {
            CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(yaw, e.get_yaw(), epsilon);
        } else {
            /* The angles get translated from 180 degrees pitch to 0 pitch and
             * 180 degrees roll and yaw which is equivalent.
             */
            CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI, e.get_roll(), epsilon);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(0, e.get_pitch(), epsilon);
            CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI, e.get_yaw(), epsilon);
        }

        roll = units::Radians(0);
        pitch = units::Radians(0);
        yaw = units::Radians(M_PI);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v(3), epsilon);

        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(yaw, e.get_yaw(), epsilon);

        roll = units::Radians(0);
        pitch = units::Radians(0);
        yaw = units::Radians(3 * M_PI);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, v(3), epsilon);

        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI, e.get_yaw(), epsilon);

        roll = units::Radians(0);
        pitch = units::Radians(0);
        yaw = units::Radians(-3 * M_PI);
        e = Euler(roll, pitch, yaw);
        q = Quaternion(e);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, fabs(v(3)), epsilon);

        e = Euler(q);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(roll, e.get_roll(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(pitch, e.get_pitch(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(M_PI, fabs(e.get_yaw()), epsilon);
    }

    void Quaternion_ut::test_Quaternion_from_DCM()
    {
        /* Example from Matlab documentation.
         */
        double epsilon = 1e-12;
        DCM dcm(0, 1, 0, 1, 0, 0, 0, 0, 1);
        Quaternion q(dcm);
        Vec3<> v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        /* Start with DCM generated from random numbers.
         */
        epsilon = 0.0001;
        dcm = DCM(0.9649, 0.9572, 0.1419, 0.1576, 0.4854, 0.4218, 0.9706,
                  0.8003, 0.9157);
        q = Quaternion(dcm);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.9409, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1058, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2316, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2235, v(3), epsilon);

        dcm = DCM(q);

        /* The conversion process changes the matrix, so we don't get the same
         * result back...
         */
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7928, dcm(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3715, dcm(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.4832, dcm(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.4696, dcm(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.8777, dcm(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.0956, dcm(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3886, dcm(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3026, dcm(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.8703, dcm(3, 3), epsilon);

        /* Convert the same DCM back to a quaternion
         */
        q = Quaternion(dcm);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.9409, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1058, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2316, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2235, v(3), epsilon);

        dcm = DCM(q);

        /* And now back to a DCM again. We should get the scaling this time.
         */
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7928, dcm(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3715, dcm(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.4832, dcm(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.4696, dcm(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.8777, dcm(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.0956, dcm(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3886, dcm(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3026, dcm(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.8703, dcm(3, 3), epsilon);

        /* 180 degree roll.
         */
        epsilon = 1e-12;
        dcm = DCM(1, 0, 0, 0, -1, 0, 0, 0, -1);
        q = Quaternion(dcm);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        dcm = DCM(q);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dcm(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, dcm(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, dcm(3, 3), epsilon);

        /* 180 degree pitch.
         */
        dcm = DCM(-1, 0, 0, 0, 1, 0, 0, 0, -1);
        q = Quaternion(dcm);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        dcm = DCM(q);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, dcm(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dcm(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, dcm(3, 3), epsilon);

        /* 180 degree yaw.
         */
        dcm = DCM(-1, 0, 0, 0, -1, 0, 0, 0, 1);
        q = Quaternion(dcm);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, v(3), epsilon);

        dcm = DCM(q);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, dcm(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, dcm(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, dcm(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, dcm(3, 3), epsilon);

        /* 90 degree roll.
         */
        epsilon = .0001;
        dcm = DCM(1, 0, 0, 0, 0, 1, 0, -1, 0);
        q = Quaternion(dcm);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);

        /* roll = pi; pitch = -pi/3; yaw = pi/6;
         */
        dcm = DCM(0.4330, 0.2500, 0.8660, -0.7500, -0.4330, 0.5000, 0.5000,
                  -0.8660, 0);
        q = Quaternion(dcm);
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6830, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1830, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, v(3), epsilon);
    }

    void Quaternion_ut::test_operator_multiply()
    {
        /* Examples from Matlab documentation.
         */
        double epsilon = 0.0001;
        Quaternion q(1, Vec3<>(0, 1, 0));
        Quaternion r(1, Vec3<>(0.5, 0.5, 0.75));

        Quaternion qr = q * r;
        Vec3<> v = qr.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2462, qr.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6155, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7385, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1231, v(3), epsilon);

        r = Quaternion(2, Vec3<>(1, 0.1, 0.1));
        qr = q * r;
        v = qr.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5996, qr.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3472, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6628, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.2840, v(3), epsilon);
    }

    void Quaternion_ut::test_operator_multiply_equal()
    {
        /* Examples from Matlab documentation.
         */
        double epsilon = 0.0001;
        Quaternion q(1, Vec3<>(0, 1, 0));
        Quaternion r(1, Vec3<>(0.5, 0.5, 0.75));

        q *= r;
        Vec3<> v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2462, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6155, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7385, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.1231, v(3), epsilon);

        q = Quaternion(1, Vec3<>(0, 1, 0));
        r = Quaternion(2, Vec3<>(1, 0.1, 0.1));
        q *= r;
        v = q.vector();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5996, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.3472, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.6628, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.2840, v(3), epsilon);
    }

    void Quaternion_ut::test_operator_multiply_vector()
    {
        /* Examples from Matlab documentation.
         */
        double epsilon = 0.0001;
        Quaternion q(1, Vec3<>(0, 1, 0));
        Vec3<> r(1, 1, 1);

        Vec3<> n = q * r;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, n(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, n(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, n(3), epsilon);

        r = Vec3<>(2, 3, 4);
        n = q * r;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-4.0, n(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(3.0, n(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, n(3), epsilon);

        q = Quaternion(1, Vec3<>(0.5, 0.3, 0.1));
        n = q * r;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.3333, n(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(5.1333, n(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.9333, n(3), epsilon);
    }

    void Quaternion_ut::test_conjugate()
    {
        double epsilon = 0.0001;
        Quaternion q(1, Vec3<>(0, 1, 0));

        q = q.conjugate();
        Vec3<> v = q.vector();

        /* We automatically normalize the quaternion.
         */
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.7071, v(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, v(3), epsilon);
    }

    void Quaternion_ut::test_inverse()
    {
        double epsilon = 0.0001;
        Quaternion q(1, Vec3<>(0, 1, 0));

        q = q.inverse();

        /* We automatically normalize the quaternion.
         */
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.7071, q.scalar(), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.vector()(1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.7071, q.vector()(2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, q.vector()(3), epsilon);
    }

} // namespace
