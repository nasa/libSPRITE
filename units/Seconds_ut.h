#ifndef __UNITS_SECONDS_UT_H__
#define __UNITS_SECONDS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Seconds_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Seconds_ut);

        /**
         * @verifies{units-15.2}
         * @verifies{units-15.7}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Seconds_ut);

} // namespace

#endif // __UNITS_SECONDS_UT_H__
