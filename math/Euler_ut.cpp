#include <math.h>
#include "math/DCM.h"
#include "math/Euler.h"
#include "math/Euler_ut.h"
#include "math/Matrix3.h"

namespace math {
    void Euler_ut::setUp()
    {
    }

    void Euler_ut::tearDown()
    {
    }

    void Euler_ut::test_Euler()
    {
        Euler e;

        CPPUNIT_ASSERT_EQUAL(0.0, double(e.get_roll()));
        CPPUNIT_ASSERT_EQUAL(0.0, double(e.get_pitch()));
        CPPUNIT_ASSERT_EQUAL(0.0, double(e.get_yaw()));

        Euler e1(units::Radians(1), units::Radians(2), units::Radians(3));

        CPPUNIT_ASSERT_EQUAL(1.0, double(e1.get_roll()));
        CPPUNIT_ASSERT_EQUAL(2.0, double(e1.get_pitch()));
        CPPUNIT_ASSERT_EQUAL(3.0, double(e1.get_yaw()));
    }

    void Euler_ut::test_roll()
    {
        const units::Radians c(1.0);
        Euler e;

        CPPUNIT_ASSERT_EQUAL(units::Radians(0), e.get_roll());

        e.set_roll(c);

        CPPUNIT_ASSERT_EQUAL(c, e.get_roll());
    }

    void Euler_ut::test_pitch()
    {
        const units::Radians c(1.0);
        Euler e;

        CPPUNIT_ASSERT_EQUAL(units::Radians(0), e.get_pitch());

        e.set_pitch(c);

        CPPUNIT_ASSERT_EQUAL(c, e.get_pitch());
    }

    void Euler_ut::test_yaw()
    {
        const units::Radians c(1.0);
        Euler e;

        CPPUNIT_ASSERT_EQUAL(units::Radians(0), e.get_yaw());

        e.set_yaw(c);

        CPPUNIT_ASSERT_EQUAL(c, e.get_yaw());
    }

    void Euler_ut::test_toDCM()
    {
        const double epsilon = .0001;

        Euler e(units::Radians(0), units::Radians(0), units::Radians(M_PI));
        DCM d = e.toDCM();
        Matrix3 m = d.toMatrix3();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, m(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, m(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(3, 3), epsilon);

        e = Euler(units::Radians(0), units::Radians(M_PI), units::Radians(0));
        d = e.toDCM();
        m = d.toMatrix3();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, m(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, m(3, 3), epsilon);

        e = Euler(units::Radians(6), units::Radians(3), units::Radians(1));
        d = e.toDCM();
        m = d.toMatrix3();

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.5349, m(1, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.8330, m(1, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1411, m(1, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.8293, m(2, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.4856, m(2, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2766, m(2, 3), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.1619, m(3, 1), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2650, m(3, 2), epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-0.9506, m(3, 3), epsilon);
    }

} // namespace
