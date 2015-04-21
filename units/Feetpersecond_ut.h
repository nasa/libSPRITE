#ifndef __UNITS_FEETPERSECOND_UT_H__
#define __UNITS_FEETPERSECOND_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Feetpersecond_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Feetpersecond_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Feetpersecond_ut);

} // namespace

#endif // __UNITS_FEETPERSECOND_UT_H__
