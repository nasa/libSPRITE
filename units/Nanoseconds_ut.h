#ifndef __UNITS_NANOSECONDS_UT_H__
#define __UNITS_NANOSECONDS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Nanoseconds_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Nanoseconds_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Nanoseconds_ut);

} // namespace

#endif // __UNITS_NANOSECONDS_UT_H__
