#include "units/Pascal.h"
#include "units/Pascal_ut.h"

namespace units {

    void Pascal_ut::setUp()
    {
    }

    void Pascal_ut::tearDown()
    {
    }

    void Pascal_ut::test()
    {
        const int32_t tval = 1000;
        Pascal p1(tval);
        Pascal p2(2);

        CPPUNIT_ASSERT_EQUAL(Pascal(tval), p1);
        CPPUNIT_ASSERT_EQUAL(tval, int32_t(p1));

        CPPUNIT_ASSERT_EQUAL(1002, int32_t(p1 + p2));
        CPPUNIT_ASSERT_EQUAL(998, int32_t(p1 - p2));
        CPPUNIT_ASSERT_EQUAL(2000, p1 * p2);
        CPPUNIT_ASSERT_EQUAL(500, p1 / p2);
        CPPUNIT_ASSERT_EQUAL(Pascal(1010u), p1 += Pascal(10));
        CPPUNIT_ASSERT_EQUAL(Pascal(1000u), p1 -= Pascal(10));
    }

} // namespace
