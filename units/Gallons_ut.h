#ifndef __UNITS_GALLONS_UT_H__
#define __UNITS_GALLONS_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Gallons_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Gallons_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Gallons_ut);

} // namespace

#endif // __UNITS_GALLONS_UT_H__
