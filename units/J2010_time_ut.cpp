#include "units/GPS_time.h"
#include "units/J2010_time.h"
#include "units/J2010_time_ut.h"

namespace units
{

    void J2010_time_ut::setUp()
    {
    }

    void J2010_time_ut::tearDown()
    {
    }

    void J2010_time_ut::test()
    {
        J2010_time t1(Days(0));
        GPS_time gps1 = GPS_time(t1);
        CPPUNIT_ASSERT_EQUAL(J2010_GPS_WEEK, gps1.week());
        CPPUNIT_ASSERT_EQUAL(J2010_GPS_SECONDS, gps1.seconds());

        t1 += Seconds(SECONDS_PER_DAY);
        CPPUNIT_ASSERT_EQUAL(Days(1), Days(t1));

        t1 += Seconds(1.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(Days(Seconds(SECONDS_PER_DAY + 1)),
                                     Days(t1), 1e-14);

        t1 -= Seconds(2.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(Days(Seconds(SECONDS_PER_DAY - 1)),
                                     Days(t1), 1e-14);

        const double t = 651.5;
        J2010_time t2(t);
        CPPUNIT_ASSERT_EQUAL(t * 24 * 3600, double(Seconds(t2)));

        gps1 = GPS_time(t2);
        CPPUNIT_ASSERT_EQUAL(t2, J2010_time(gps1));
    }

} // namespace
