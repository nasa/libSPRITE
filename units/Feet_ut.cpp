#include "units/Kilometers.h"
#include "units/Meters.h"
#include "units/Feet.h"
#include "units/Miles.h"
#include "units/Feet_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Feet_ut::setUp()
    {
    }


    void Feet_ut::tearDown()
    {
    }


    void Feet_ut::test()
    {

        const double KILOMETERS_PER_FOOT = 0.381 / 1250;
        const double METERS_PER_FOOT     = 381.0 / 1250;
        const double MILES_PER_FOOT      = 1.0 / 5280;
        const double EPSILON             = 1e-12;

        Kilometers  km(KILOMETERS_PER_FOOT);
        Meters  m(METERS_PER_FOOT);

        Feet f(1.0);
        Miles mi(MILES_PER_FOOT);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(f, Feet(km), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(f, Feet(m), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(f, Feet(f), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(f, Feet(mi), EPSILON);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(MILES_PER_FOOT, f.toMiles(), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(METERS_PER_FOOT, f.toMeters(), EPSILON);

        f = Feet(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, f, EPSILON);

        f = Feet(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, f, EPSILON);

    }

} // namespace
