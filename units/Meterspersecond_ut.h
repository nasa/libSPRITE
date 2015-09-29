#ifndef __UNITS_METERSPERSECOND_UT_H__
#define __UNITS_METERSPERSECOND_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Meterspersecond_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Meterspersecond_ut);

        /**
         * @verifies{units-9.2}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Meterspersecond_ut);

} // namespace

#endif // __UNITS_METERSPERSECOND_UT_H__
