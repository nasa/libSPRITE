#include "units/Meterspersecondpersecond.h"
#include "units/Meterspersecondpersecond_ut.h"
#include "base/XPRINTF.h"

namespace units {

    void Meterspersecondpersecond_ut::setUp()
    {
    }

    void Meterspersecondpersecond_ut::tearDown()
    {
    }

    void Meterspersecondpersecond_ut::test()
    {

        const double EPSILON = 1e-12;

        Meterspersecondpersecond mpsps(1.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(mpsps, Meterspersecondpersecond(mpsps),
                                     EPSILON);

        mpsps = Meterspersecondpersecond(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, mpsps, EPSILON);

        mpsps = Meterspersecondpersecond(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, mpsps, EPSILON);
    }

} // namespace
