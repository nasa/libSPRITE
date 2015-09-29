#include "units/Nanoseconds.h"
#include "units/Seconds.h"
#include "units/Seconds_ut.h"

namespace units {

    void Seconds_ut::setUp()
    {
    }

    void Seconds_ut::tearDown()
    {
    }

    void Seconds_ut::test()
    {
        const unsigned int NSEC_PER_SECOND = 1000000000;
        Seconds s(1.0);
        Nanoseconds n(NSEC_PER_SECOND);

        CPPUNIT_ASSERT_EQUAL(Seconds(n), s);

        s = Seconds(2 * 3);

        double epsilon = 1e-12;
        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, s, epsilon);

        s = Seconds(2.0 * 4.0);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(8.0, s, epsilon);
    }

} // namespace
