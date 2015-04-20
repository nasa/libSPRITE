#include "units/Liters.h"
#include "units/Liters_ut.h"
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

        const double EPSILON           = 1e-12;

        Liters      l(1.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(l, Liters(l), EPSILON);

        l = Liters(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, l, EPSILON);

        l = Liters(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, l, EPSILON);
    }

} // namespace
