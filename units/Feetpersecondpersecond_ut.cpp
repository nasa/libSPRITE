#include "units/Feetpersecondpersecond.h"
#include "units/Meterspersecondpersecond.h"
#include "units/Feetpersecondpersecond_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Feetpersecondpersecond_ut::setUp()
    {
    }


    void Feetpersecondpersecond_ut::tearDown()
    {
    }


    void Feetpersecondpersecond_ut::test()
    {

        const double METERS_PER_FOOT = 381.0 / 1250;
        const double EPSILON         = 1e-12;


        Feetpersecondpersecond fpsps(1.0);
        Meterspersecondpersecond mpsps(METERS_PER_FOOT);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(fpsps, Feetpersecondpersecond(mpsps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(fpsps, Feetpersecondpersecond(fpsps), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(METERS_PER_FOOT, fpsps.toMeterspersecondpersecond(), EPSILON);

        fpsps = Feetpersecondpersecond(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, fpsps, EPSILON);

        fpsps = Feetpersecondpersecond(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, fpsps, EPSILON);

    }

} // namespace
