#ifndef __UNITS_KILOMETERS_UT_H__
#define __UNITS_KILOMETERS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Kilometers_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Kilometers_ut);

        /**
         * verifies{units-6.2}
         * verifies{units-6.6}
         * verifies{units-6.7}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Kilometers_ut);

} // namespace

#endif // __UNITS_KILOMETERS_UT_H__
