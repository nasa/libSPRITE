#ifndef __UNITS_KILOMETERSPERHOUR_UT_H__
#define __UNITS_KILOMETERSPERHOUR_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Kilometersperhour_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Kilometersperhour_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Kilometersperhour_ut);

} // namespace

#endif // __UNITS_KILOMETERSPERHOUR_UT_H__
