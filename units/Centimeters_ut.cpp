#include "Centimeters.h"
#include "Kilometers.h"
#include "Meters.h"
#include "Feet.h"
#include "Miles.h"
#include "Yards.h"
#include "Centimeters_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Centimeters_ut::setUp()
    {
    }


    void Centimeters_ut::tearDown()
    {
    }


    void Centimeters_ut::test()
    {


        const double KILOMETERS_PER_CENTIMETER  = 0.00001;
        const double METERS_PER_CENTIMETER      = 0.01;
        const double FEET_PER_CENTIMETER        = 12.50 / 381.0;
        const double YARDS_PER_CENTIMETER       = 12.50 / 1143.0;
        const double MILES_PER_CENTIMETER       = 1.25  / 201168.0;
        const double EPSILON                    = 1e-12;

        Centimeters cm(1.0);
        Kilometers  km(KILOMETERS_PER_CENTIMETER);
        Meters m(METERS_PER_CENTIMETER);

        Feet  f(FEET_PER_CENTIMETER);
        Miles mi(MILES_PER_CENTIMETER);
        Yards y(YARDS_PER_CENTIMETER);


        CPPUNIT_ASSERT_EQUAL(cm, Centimeters(cm));
        CPPUNIT_ASSERT_EQUAL(cm, Centimeters(km));
        CPPUNIT_ASSERT_EQUAL(cm, Centimeters(m));
        CPPUNIT_ASSERT_DOUBLES_EQUAL(cm, Centimeters(f), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(cm, Centimeters(mi), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(cm, Centimeters(y), EPSILON);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(METERS_PER_CENTIMETER, cm.toMeters(), EPSILON);

        cm = Centimeters(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, cm, EPSILON);

        cm = Centimeters(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, cm, EPSILON);


    }

} // namespace
