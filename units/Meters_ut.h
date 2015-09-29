#ifndef __UNITS_METERS_UT_H__
#define __UNITS_METERS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Meters_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Meters_ut);

        /**
         * @verifies{units-8.2}
         * @verifies{units-8.3}
         * @verifies{units-8.10}
         * @verifies{units-8.11}
         */
        CPPUNIT_TEST(test);

        /**
         * @verifies{units-8.12}
         * @verifies{units-8.13}
         */
        CPPUNIT_TEST(test_millimeters);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
        void test_millimeters();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Meters_ut);

} // namespace

#endif // __UNITS_METERS_UT_H__
