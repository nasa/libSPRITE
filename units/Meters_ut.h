#ifndef __UNITS_METERS_UT_H__
#define __UNITS_METERS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Meters_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Meters_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Meters_ut);

} // namespace

#endif // __UNITS_METERS_UT_H__
