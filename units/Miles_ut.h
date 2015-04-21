#ifndef __UNITS_MILES_UT_H__
#define __UNITS_MILES_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Miles_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Miles_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Miles_ut);

} // namespace

#endif // __UNITS_MILES_UT_H__
