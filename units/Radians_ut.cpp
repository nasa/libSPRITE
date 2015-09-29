#include <math.h>
#include "units/Degrees.h"
#include "units/Radians.h"
#include "units/Radians_ut.h"

namespace units {
    void Radians_ut::setUp()
    {
    }

    void Radians_ut::tearDown()
    {
    }

    void Radians_ut::default_constructor()
    {
        Radians r;

        CPPUNIT_ASSERT_EQUAL(0.0, double(r));
    }

    void Radians_ut::test()
    {
        Radians r(M_PI);
        Degrees d(180);

        CPPUNIT_ASSERT(Radians(M_PI) == r);
        CPPUNIT_ASSERT(r == Radians(d));

        r = Radians(2 * M_PI);
        d = Degrees(360);

        CPPUNIT_ASSERT(2 * M_PI == r);
        CPPUNIT_ASSERT(r == Radians(d));

        r = Radians(-M_PI);
        d = Degrees(-180);

        CPPUNIT_ASSERT(-M_PI == r);
        CPPUNIT_ASSERT(r == Radians(d));
    }

} // namespace
