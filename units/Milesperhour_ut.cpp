#include "units/Kilometersperhour.h"
#include "units/Meterspersecond.h"
#include "units/Feetpersecond.h"
#include "units/Milesperhour.h"
#include "Milesperhour_ut.h"
#include "base/XPRINTF.h"


namespace units
{

    void Milesperhour_ut::setUp()
    {
    }


    void Milesperhour_ut::tearDown()
    {
    }


    void Milesperhour_ut::test()
    {

        const double MPH_TO_KPH    = 201.168 / 125;
        const double MPH_TO_MPS    = 1397.0 / 3125;
        const double MPH_TO_FPS    = 66.0 / 45;
        const double EPSILON       = 1e-12;

        Kilometersperhour     kph(MPH_TO_KPH);
        Meterspersecond       mps(MPH_TO_MPS);
        Feetpersecond         fps(MPH_TO_FPS);
        Milesperhour          mph(1.0);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(mph, Milesperhour(kph), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mph, Milesperhour(mps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mph, Milesperhour(fps), EPSILON);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(mph, Milesperhour(mph), EPSILON);


        CPPUNIT_ASSERT_DOUBLES_EQUAL(MPH_TO_FPS, mph.toFeetpersecond(), EPSILON);

        mph = Milesperhour(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, mph, EPSILON);

        mph = Milesperhour(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, mph, EPSILON);


        mph = Milesperhour(30);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(44.0, mph.toFeetpersecond(), EPSILON);
    }

} // namespace
