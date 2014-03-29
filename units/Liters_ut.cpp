#include "Liters.h"
#include "Gallons.h"
#include "Liters_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Liters_ut::setUp()
    {
    }


    void Liters_ut::tearDown()
    {
    }


    void Liters_ut::test()
    {

        const double LITERS_TO_GALLONS = 1 / 3.785411784;
        const double EPSILON           = 1e-12;

        Liters      l(1.0);
        Gallons     g(LITERS_TO_GALLONS);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(l, Liters(l), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(l, Liters(g), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(LITERS_TO_GALLONS, l.toGallons(), EPSILON);

        l = Liters(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, l, EPSILON);

        l = Liters(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, l, EPSILON);


        l = Liters(30);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(7.92516157, l.toGallons(), 1e-6);
    }

} // namespace
