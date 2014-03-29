#include "Kilometersperhour.h"
#include "Meterspersecond.h"
#include "Feetpersecond.h"
#include "Milesperhour.h"
#include "Kilometersperhour_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Kilometersperhour_ut::setUp()
    {
    }


    void Kilometersperhour_ut::tearDown()
    {
    }


    void Kilometersperhour_ut::test()
    {

        const double KPH_TO_MPS    = 1 / 3.6;
        const double KPH_TO_FPS    = 25 / 27.432;
        const double KPH_TO_MPH    = 125 / 201.168;
        const double EPSILON       = 1e-12;

        Kilometersperhour     kph(1.0);
        Meterspersecond       mps(KPH_TO_MPS);
        Feetpersecond         fps(KPH_TO_FPS);
        Milesperhour          mph(KPH_TO_MPH);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(kph, Kilometersperhour(kph), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(kph, Kilometersperhour(mps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(kph, Kilometersperhour(fps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(kph, Kilometersperhour(mph), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(KPH_TO_MPS, kph.toMeterspersecond(), EPSILON);

        kph = Kilometersperhour(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, kph, EPSILON);

        kph = Kilometersperhour(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, kph, EPSILON);


        kph = Kilometersperhour(30);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(8.33333333333333, kph.toMeterspersecond(), EPSILON);

    }

} // namespace
