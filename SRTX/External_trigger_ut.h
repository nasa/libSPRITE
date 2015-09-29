#ifndef __SRTX_EXTERNAL_TRIGGER_UT_H__
#define __SRTX_EXTERNAL_TRIGGER_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SRTX {
    /**
     * Provide tests for initiating the SRTX scheduler from an external trigger.
     */
    class External_trigger_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(External_trigger_ut);

        CPPUNIT_TEST(test_trigger);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        /**
         * This test verifies that the scheduler can be trigger by an external
         * source.
         */
        void test_trigger();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(External_trigger_ut);

} // namespace

#endif // __SRTX_EXTERNAL_TRIGGER_UT_H__
