#include "trig_ut.h"
#include "trig.h"

namespace math {

    namespace {
        double DELTA = 1e-12;
    }

    void trig_ut::setUp()
    {
    }

    void trig_ut::tearDown()
    {
    }

    void trig_ut::test_sin()
    {
        // Radians
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sin(units::Radians(0)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, sin(units::Radians(M_PI / 2)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sin(units::Radians(M_PI)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, sin(units::Radians(M_PI * 1.5)),
                                     DELTA);

        // Degrees
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sin(units::Degrees(0)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, sin(units::Degrees(90)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, sin(units::Degrees(180)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, sin(units::Degrees(270)), DELTA);
    }

    void trig_ut::test_cos()
    {
        // Radians
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cos(units::Radians(0)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, cos(units::Radians(M_PI / 2)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, cos(units::Radians(M_PI)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, cos(units::Radians(M_PI * 1.5)),
                                     DELTA);

        // Degrees
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, cos(units::Degrees(0)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, cos(units::Degrees(90)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, cos(units::Degrees(180)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, cos(units::Degrees(270)), DELTA);
    }

    void trig_ut::test_tan()
    {
        // Radians
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, tan(units::Radians(0)), DELTA);
        CPPUNIT_ASSERT_THROW(tan(units::Radians(M_PI / 2)), int);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, tan(units::Radians(M_PI / 4)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, tan(units::Radians(M_PI)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, tan(units::Radians(M_PI * 0.75)),
                                     DELTA);

        // Degrees
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, tan(units::Degrees(0)), DELTA);
        CPPUNIT_ASSERT_THROW(tan(units::Degrees(90)), int);
        CPPUNIT_ASSERT_THROW(tan(units::Degrees(-90)), int);
        CPPUNIT_ASSERT_THROW(tan(units::Degrees(360 + 90)), int);
        CPPUNIT_ASSERT_THROW(tan(units::Degrees(-180 - 90)), int);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, tan(units::Degrees(45)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, tan(units::Degrees(180)), DELTA);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, tan(units::Degrees(135)), DELTA);
    }

} // namespace
