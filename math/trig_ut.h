#ifndef __MATH_TRIG_UT_H__
#define __MATH_TRIG_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace math
{
    class trig_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(trig_ut);

        CPPUNIT_TEST(test_sin);
        CPPUNIT_TEST(test_cos);
        CPPUNIT_TEST(test_tan);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_sin();
        void test_cos();
        void test_tan();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(trig_ut);

} // namespace

#endif // __MATH_TRIG_UT_H__
