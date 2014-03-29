#include "Centimeters.h"
#include "Kilometers.h"
#include "Meters.h"
#include "Feet.h"
#include "Miles.h"
#include "Yards.h"
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

        const double CENTIMETERS_PER_MILE = 201168 / 1.25;
        const double KILOMETERS_PER_MILE = 201168 / 125000.0;
        const double METERS_PER_MILE     = 201168 / 125.0;
        const double FEET_PER_MILE       = 5280.0;
        const double YARDS_PER_MILE      = 5280.0 / 3;
        const double EPSILON             = 1e-12;

        Centimeters cm(CENTIMETERS_PER_MILE);
        Kilometers  km(KILOMETERS_PER_MILE);
        Meters  m(METERS_PER_MILE);

        Feet f(FEET_PER_MILE);
        Miles mi(1.0);
        Yards y(YARDS_PER_MILE);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(cm), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(km), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(m), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(f), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(mi), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mi, Miles(y), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(FEET_PER_MILE, mi.toFeet(), EPSILON);

        mi = Miles(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, mi, EPSILON);

        mi = Miles(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, mi, EPSILON);

    }

} // namespace
