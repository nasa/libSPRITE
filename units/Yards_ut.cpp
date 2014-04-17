#include "units/Centimeters.h"
#include "units/Kilometers.h"
#include "units/Meters.h"
#include "units/Feet.h"
#include "units/Miles.h"
#include "units/Yards.h"
#include "units/Yards_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Yards_ut::setUp()
    {
    }


    void Yards_ut::tearDown()
    {
    }


    void Yards_ut::test()
    {

        const double CENTIMETERS_PER_YARD = 114300.0 / 1250;
        const double KILOMETERS_PER_YARD  = 1.143    / 1250;
        const double METERS_PER_YARD      = 1143.0   / 1250;
        const double FEET_PER_YARD        = 3.0;
        const double MILES_PER_YARD       = 1.0 / 1760;
        const double EPSILON              = 1e-12;

        Centimeters cm(CENTIMETERS_PER_YARD);
        Kilometers  km(KILOMETERS_PER_YARD);
        Meters  m(METERS_PER_YARD);

        Feet f(FEET_PER_YARD);
        Miles mi(MILES_PER_YARD);
        Yards y(1.0);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(y, Yards(cm), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(y, Yards(km), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(y, Yards(m), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(y, Yards(f), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(y, Yards(mi), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(y, Yards(y), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(FEET_PER_YARD, y.toFeet(), EPSILON);

        y = Yards(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, y, EPSILON);

        y = Yards(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, y, EPSILON);

    }

} // namespace
