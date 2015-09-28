#ifndef __UTIL_SMOOTH_UT_H__
#define __UTIL_SMOOTH_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace util {

    class Smooth_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Smooth_ut);

        /**
         * @verifies{util-3.1}
         */
        CPPUNIT_TEST(test_savgol_cubic);

        /**
         * @verifies{util-4.1}
         */
        CPPUNIT_TEST(test_savgol_cubic_dx);

        CPPUNIT_TEST_SUITE_END();

      public:
        Smooth_ut();

        void setUp();
        void tearDown();

      protected:
        void test_savgol_cubic();
        void test_savgol_cubic_dx();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Smooth_ut);

} // namespace

#endif // __UTIL_SMOOTH_UT_H__
