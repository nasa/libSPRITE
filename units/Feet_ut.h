#ifndef __UNITS_FEET_UT_H__
#define __UNITS_FEET_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Feet_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Feet_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Feet_ut);

} // namespace

#endif // __UNITS_FEET_UT_H__
