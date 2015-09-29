#include "units/Nanoseconds.h"
#include "units/GPS_time.h"
#include "units/GPS_time_ut.h"

namespace units {

    void GPS_time_ut::setUp()
    {
    }

    void GPS_time_ut::tearDown()
    {
    }

    void GPS_time_ut::test()
    {
        GPS_time t1;
        CPPUNIT_ASSERT_EQUAL(1, t1.week());
        CPPUNIT_ASSERT_EQUAL(Seconds(0.0), t1.seconds());

        /* Add a bit more than a week and make sure the values incremented
         * properly.
         */
        t1 += Seconds(604801);

        /* Make sure fractions of a second work too.
         */
        t1 += Seconds(604801.999);

        CPPUNIT_ASSERT_EQUAL(3, t1.week());
        CPPUNIT_ASSERT_DOUBLES_EQUAL(Seconds(2.999), t1.seconds(), 1e-8);

        GPS_time t2(1, Seconds(1.0));
        CPPUNIT_ASSERT_EQUAL(1, t2.week());
        CPPUNIT_ASSERT_EQUAL(Seconds(1.0), t2.seconds());
    }

} // namespace
