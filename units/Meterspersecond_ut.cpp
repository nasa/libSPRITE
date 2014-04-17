#include "units/Kilometersperhour.h"
#include "units/Meterspersecond.h"
#include "units/Feetpersecond.h"
#include "units/Milesperhour.h"
#include "Meterspersecond_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Meterspersecond_ut::setUp()
    {
    }


    void Meterspersecond_ut::tearDown()
    {
    }


    void Meterspersecond_ut::test()
    {

        const double MPS_TO_KPH         = 3.6;
        const double MPS_TO_FPS         = 1250.0 / 381;
        const double MPS_TO_MPH         = 3125.0 / 1397;
        const double EPSILON            = 1e-12;

        Kilometersperhour     kph(MPS_TO_KPH);
        Meterspersecond       mps(1.0);
        Feetpersecond         fps(MPS_TO_FPS);
        Milesperhour          mph(MPS_TO_MPH);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(mps, Meterspersecond(kph), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mps, Meterspersecond(mps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mps, Meterspersecond(fps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mps, Meterspersecond(mph), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(MPS_TO_KPH, mps.toKilometersperhour(), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(MPS_TO_FPS, mps.toFeetpersecond(), EPSILON);

        mps = Meterspersecond(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, mps, EPSILON);

        mps = Meterspersecond(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, mps, EPSILON);


        mps = Meterspersecond(30);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(108, mps.toKilometersperhour(), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(98.425196850393701, mps.toFeetpersecond(), EPSILON);
    }

} // namespace
