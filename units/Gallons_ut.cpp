#include "Liters.h"
#include "Gallons.h"
#include "Gallons_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Gallons_ut::setUp()
    {
    }


    void Gallons_ut::tearDown()
    {
    }


    void Gallons_ut::test()
    {

        const double GALLONS_TO_LITERS = 3.785411784;
        const double EPSILON           = 1e-12;

        Liters      l(GALLONS_TO_LITERS);
        Gallons     g(1.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(g, Gallons(l), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(g, Gallons(g), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(GALLONS_TO_LITERS, g.toLiters(), EPSILON);

        g = Gallons(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, g, EPSILON);

        g = Gallons(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, g, EPSILON);


        g = Gallons(30);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(113.562354, g.toLiters(), 1e-6);

    }

} // namespace
