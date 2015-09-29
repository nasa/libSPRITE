#include "units/Nanoseconds.h"
#include "units/Seconds.h"
#include "units/Nanoseconds_ut.h"

namespace units {

    void Nanoseconds_ut::setUp()
    {
    }

    void Nanoseconds_ut::tearDown()
    {
    }

    void Nanoseconds_ut::test()
    {
        const unsigned int NSEC_PER_SECOND = 1000000000;
        Nanoseconds n(1);
        Seconds s(1.0 / NSEC_PER_SECOND);

        CPPUNIT_ASSERT_EQUAL(Nanoseconds(s), n);

        n = Nanoseconds(2 * 3);

        int64_t ex = 6;
        CPPUNIT_ASSERT_EQUAL(ex, int64_t(n));
    }

} // namespace
