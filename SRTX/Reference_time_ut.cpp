#include "SRTX/Reference_time_ut.h"
#include "SRTX/Reference_time.h"

namespace SRTX {

    void Reference_time_ut::setUp()
    {
    }

    void Reference_time_ut::tearDown()
    {
    }

    void Reference_time_ut::test_reference_time()
    {
        units::Nanoseconds ref_time = get_reference_time();

        CPPUNIT_ASSERT(0 == ref_time);

        Reference_time &rtimer = Reference_time::get_instance();

        ref_time = rtimer.increment(units::MSEC);

        CPPUNIT_ASSERT_EQUAL(units::MSEC, rtimer.get_time());
    }

} // namespace
