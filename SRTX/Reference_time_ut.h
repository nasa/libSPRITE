#ifndef __SRTX_REFERENCE_TIME_UT_H__
#define __SRTX_REFERENCE_TIME_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace sys {
    /**
     * Test the reference time class.
     */
    class Reference_time_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Reference_time_ut);

        CPPUNIT_TEST(test_reference_time);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        /**
         * Test the ability to get and set reference time.
         */
        void test_reference_time();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Reference_time_ut);

} // namespace

#endif // __SRTX_REFERENCE_TIME_UT_H__
