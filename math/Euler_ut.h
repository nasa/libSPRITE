#ifndef __MATH_EULER_UT_H__
#define __MATH_EULER_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace math {
    class Euler_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Euler_ut);

        CPPUNIT_TEST(test_Euler);
        CPPUNIT_TEST(test_roll);
        CPPUNIT_TEST(test_pitch);
        CPPUNIT_TEST(test_yaw);
        CPPUNIT_TEST(test_toDCM);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_Euler();
        void test_roll();
        void test_pitch();
        void test_yaw();
        void test_toDCM();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Euler_ut);

} // namespace

#endif // __MATH_EULER_UT_H__
