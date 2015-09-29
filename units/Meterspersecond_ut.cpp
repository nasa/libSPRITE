#include "units/Meterspersecond.h"
#include "Meterspersecond_ut.h"
#include "base/XPRINTF.h"

namespace units {

    void Meterspersecond_ut::setUp()
    {
    }

    void Meterspersecond_ut::tearDown()
    {
    }

    void Meterspersecond_ut::test()
    {

        const double EPSILON = 1e-12;

        Meterspersecond mps(1.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(mps, Meterspersecond(mps), EPSILON);

        mps = Meterspersecond(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, mps, EPSILON);

        mps = Meterspersecond(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, mps, EPSILON);

        mps = Meterspersecond(30);
    }

} // namespace
