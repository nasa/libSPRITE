#ifndef __UNITS_MILLIMETERS_UT_H__
#define __UNITS_MILLIMETERS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Millimeters_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Millimeters_ut);

        /**
         * @verifies{units-17.2}
         * @verifies{units-17.3}
         */
        CPPUNIT_TEST(test);

        /**
         * @verifies{units-17.10}
         * @verifies{units-17.11}
         */
        CPPUNIT_TEST(test_meters);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
        void test_meters();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Millimeters_ut);

} // namespace

#endif // __UNITS_MILLIMETERS_UT_H__
