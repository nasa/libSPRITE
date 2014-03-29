#include "Kilometersperhour.h"
#include "Meterspersecond.h"
#include "Feetpersecond.h"
#include "Milesperhour.h"
#include "Feetpersecond_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Feetpersecond_ut::setUp()
    {
    }


    void Feetpersecond_ut::tearDown()
    {
    }


    void Feetpersecond_ut::test()
    {

        const double FPS_TO_KPH         = 27.432 / 25;
        const double FPS_TO_MPS         = 381.0 / 1250;
        const double FPS_TO_MPH         = 45 / 66.0;
        const double EPSILON            = 1e-12;

        Kilometersperhour     kph(FPS_TO_KPH);
        Meterspersecond       mps(FPS_TO_MPS);

        Feetpersecond    fps(1.0);
        Milesperhour     mph(FPS_TO_MPH);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(fps, Feetpersecond(kph), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(fps, Feetpersecond(mps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(fps, Feetpersecond(fps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(fps, Feetpersecond(mph), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(FPS_TO_MPH, fps.toMilesperhour(), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(FPS_TO_MPS, fps.toMeterspersecond(), EPSILON);

        fps = Feetpersecond(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, fps, EPSILON);

        fps = Feetpersecond(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, fps, EPSILON);


        fps = Feetpersecond(30);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(20.4545454545454545, fps.toMilesperhour(), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(9.144, fps.toMeterspersecond(), EPSILON);




    }

} // namespace
