#include "SRTX/RTC_ut.h"
#include "SRTX/RTC.h"

namespace SRTX {

    void RTC_ut::setUp()
    {
    }

    void RTC_ut::tearDown()
    {
    }

    void RTC_ut::test_RTC()
    {
        units::Nanoseconds delay = units::SEC;
        units::Nanoseconds start_time;
        units::Nanoseconds end_time;

        CPPUNIT_ASSERT_EQUAL(true, get_time(start_time));
        CPPUNIT_ASSERT_EQUAL(true, sleep(delay));
        CPPUNIT_ASSERT_EQUAL(true, get_time(end_time));

        CPPUNIT_ASSERT(end_time > start_time + delay);
    }

} // namespace
