#ifndef __SRTX_RTC_UT_H__
#define __SRTX_RTC_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SRTX {
    /**
     * Test the reference time class.
     */
    class RTC_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(RTC_ut);

        CPPUNIT_TEST(test_RTC);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        /**
         * Test the ability to get the system time and sleep for a specified
         * period of time.
         */
        void test_RTC();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(RTC_ut);

} // namespace

#endif // __SRTX_RTC_UT_H__
