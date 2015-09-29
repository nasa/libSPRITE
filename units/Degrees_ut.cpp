#include <math.h>
#include "units/Degrees.h"
#include "units/Radians.h"
#include "units/Degrees_ut.h"

namespace units {

    void Degrees_ut::setUp()
    {
    }

    void Degrees_ut::tearDown()
    {
    }

    void Degrees_ut::test()
    {
        Degrees d(180);
        Radians r(M_PI);

        CPPUNIT_ASSERT(Degrees(180) == d);
        CPPUNIT_ASSERT(d == Degrees(r));

        d = Degrees(360);
        r = Radians(2 * M_PI);

        CPPUNIT_ASSERT(360 == d);
        CPPUNIT_ASSERT(d == Degrees(r));

        d = Degrees(-180);
        r = Radians(-M_PI);

        CPPUNIT_ASSERT(-180 == d);
        CPPUNIT_ASSERT(d == Degrees(r));
    }

} // namespace
