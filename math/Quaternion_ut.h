#ifndef __MATH_QUATERNION_UT_H__
#define __MATH_QUATERNION_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace math {
    class Quaternion_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Quaternion_ut);

        CPPUNIT_TEST(test_Quaternion);
        CPPUNIT_TEST(test_Quaternion_from_scalar_vector);
#if 0
        CPPUNIT_TEST(test_Quaternion_from_angle_vector);
#endif
        CPPUNIT_TEST(test_Quaternion_from_Euler);
        CPPUNIT_TEST(test_Quaternion_from_DCM);
        CPPUNIT_TEST(test_operator_multiply);
        CPPUNIT_TEST(test_operator_multiply_equal);
        CPPUNIT_TEST(test_operator_multiply_vector);
        CPPUNIT_TEST(test_conjugate);
        CPPUNIT_TEST(test_inverse);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_Quaternion();
        void test_Quaternion_from_scalar_vector();
#if 0
        void test_Quaternion_from_angle_vector();
#endif
        void test_Quaternion_from_Euler();
        void test_Quaternion_from_DCM();
        void test_operator_multiply();
        void test_operator_multiply_equal();
        void test_operator_multiply_vector();
        void test_conjugate();
        void test_inverse();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Quaternion_ut);

} // namespace

#endif // __MATH_QUATERNION_UT_H__
