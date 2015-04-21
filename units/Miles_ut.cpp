#include "units/Kilometers.h"
#include "units/Meters.h"
#include "units/Feet.h"
#include "units/Miles.h"
#include "Miles_ut.h"
#include "base/XPRINTF.h"

namespace units
{

    void Miles_ut::setUp()
    {
    }

    void Miles_ut::tearDown()
    {
    }

    void Miles_ut::test()
    {
        const double KILOMETERS_PER_MILE = 201168 / 125000.0;
        const double METERS_PER_MILE = 201168 / 125.0;
        const double FEET_PER_MILE = 5280.0;
        const double EPSILON = 1e-12;

        Kilometers km(KILOMETERS_PER_MILE);
        Meters m(METERS_PER_MILE);

        Feet f(FEET_PER_MILE);
        Miles mi(1.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(km), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(m), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(f), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(mi), EPSILON);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(FEET_PER_MILE, mi.toFeet(), EPSILON);

        mi = Miles(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, mi, EPSILON);

        mi = Miles(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, mi, EPSILON);
    }

} // namespace
