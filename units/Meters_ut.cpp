#include "Centimeters.h"
#include "Kilometers.h"
#include "Meters.h"
#include "Feet.h"
#include "Miles.h"
#include "Yards.h"
#include "Meters_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Meters_ut::setUp()
    {
    }


    void Meters_ut::tearDown()
    {
    }


    void Meters_ut::test()
    {

        const double CENTIMETERS_PER_METER = 100.0;
        const double KILOMETERS_PER_METER  = 0.001;
        const double FEET_PER_METER        = 1250 / 381.0;
        const double YARDS_PER_METER       = 1250 / 1143.0;
        const double MILES_PER_METER       = 125  / 201168.0;
        const double EPSILON               = 1e-12;

        Meters m(1.0);
        Kilometers  km(KILOMETERS_PER_METER);
        Centimeters cm(CENTIMETERS_PER_METER);

        Feet  f(FEET_PER_METER);
        Miles mi(MILES_PER_METER);
        Yards y(YARDS_PER_METER);


        CPPUNIT_ASSERT_EQUAL(m, Meters(cm));
        CPPUNIT_ASSERT_EQUAL(m, Meters(km));
        CPPUNIT_ASSERT_EQUAL(m, Meters(m));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(m, Meters(f), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(m, Meters(mi), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(m, Meters(y), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(CENTIMETERS_PER_METER, m.toCentimeters(), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(KILOMETERS_PER_METER, m.toKilometers(), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(FEET_PER_METER, m.toFeet(), EPSILON);

        m = Meters(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, m, EPSILON);

        m = Meters(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, m, EPSILON);

    }

} // namespace
