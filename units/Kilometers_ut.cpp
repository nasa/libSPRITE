#include "units/Kilometers.h"
#include "units/Meters.h"
#include "units/Feet.h"
#include "units/Miles.h"
#include "units/Kilometers_ut.h"
#include "base/XPRINTF.h"

namespace units
{

    void Kilometers_ut::setUp()
    {
    }

    void Kilometers_ut::tearDown()
    {
    }

    void Kilometers_ut::test()
    {

        const double METERS_PER_KILOMETER = 1000;
        const double FEET_PER_KILOMETER = 1250000 / 381.0;
        const double MILES_PER_KILOMETER = 125000 / 201168.0;
        const double EPSILON = 1e-12;

        Kilometers km(1.0);
        Meters m(METERS_PER_KILOMETER);

        Feet f(FEET_PER_KILOMETER);
        Miles mi(MILES_PER_KILOMETER);

        CPPUNIT_ASSERT_EQUAL(km, Kilometers(km));
        CPPUNIT_ASSERT_EQUAL(km, Kilometers(m));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(km, Kilometers(f), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(km, Kilometers(mi), EPSILON);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(METERS_PER_KILOMETER, km.toMeters(),
                                     EPSILON);

        km = Kilometers(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, km, EPSILON);

        km = Kilometers(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, km, EPSILON);
    }

} // namespace
