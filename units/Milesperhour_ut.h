#ifndef __UNITS_MILESPERHOUR_UT_H__
#define __UNITS_MILESPERHOUR_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units
{
    class Milesperhour_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Milesperhour_ut);

        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Milesperhour_ut);

} // namespace

#endif // __UNITS_MILESPERHOUR_UT_H__
