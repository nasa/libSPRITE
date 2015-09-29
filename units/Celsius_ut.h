#ifndef __UNITS_CELSIUS_UT_H__
#define __UNITS_CELSIUS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Celsius_ut : public CppUnit::TestFixture {
        CPPUNIT_TEST_SUITE(Celsius_ut);

        /**
         * @verifies{units-1.1}
         * @verifies{units-1.2}
         * @verifies{units-1.3}
         * @verifies{units-1.5}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Celsius_ut);

} // namespace

#endif // __UNITS_CELSIUS_UT_H__
