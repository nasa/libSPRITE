#ifndef __UNITS_LITERS_UT_H__
#define __UNITS_LITERS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Liters_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Liters_ut);

        /**
         * @verifies{units-7.2}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Liters_ut);

} // namespace

#endif // __UNITS_LITERS_UT_H__
