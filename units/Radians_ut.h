#ifndef __UNITS_RADIANS_UT_H__
#define __UNITS_RADIANS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Radians_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Radians_ut);

        /**
         * @verifies{units-13.1}
         */
        CPPUNIT_TEST(default_constructor);

        /**
         * @verifies{units-13.2}
         * @verifies{units-13.7}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void default_constructor();
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Radians_ut);

} // namespace

#endif // __UNITS_RADIANS_UT_H__
