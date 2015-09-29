#ifndef __UNITS_METERSPERSECONDPERSECOND_UT_H__
#define __UNITS_METERSPERSECONDPERSECOND_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class Meterspersecondpersecond_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Meterspersecondpersecond_ut);

        /**
         * @verifies{units-10.2}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Meterspersecondpersecond_ut);

} // namespace

#endif // __UNITS_METERSPERSECONDPERSECOND_UT_H__
