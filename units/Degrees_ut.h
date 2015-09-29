#ifndef __UNITS_DEGREES_UT_H__
#define __UNITS_DEGREES_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Degrees_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Degrees_ut);

        /**
         * @verifies{units-3.2}
         * @verifies{units-3.6}
         * @verifies{units-3.7}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Degrees_ut);

} // namespace

#endif // __UNITS_DEGREES_UT_H__
