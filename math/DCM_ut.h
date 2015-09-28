#ifndef __MATH_DCM_UT_H__
#define __MATH_DCM_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace math {
    class DCM_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(DCM_ut);

        /**
         * @verifies{math-7.3}
         * @verifies{math-7.5}
         * @verifies{math-7.6}
         */
        CPPUNIT_TEST(test_DCM);

        /**
         * @verifies{math-7.5}
         * @verifies{math-7.6}
         */
        CPPUNIT_TEST(test_Euler_to_DCM);

        /**
         * @verifies{math-7.5}
         * @verifies{math-7.9}
         */
        CPPUNIT_TEST(test_multiply_vector);

        /**
         * @verifies{math-7.5}
         * @verifies{math-7.10}
         */
        CPPUNIT_TEST(test_transpose);

        /**
         * @verifies{math-7.5}
         * @verifies{math-7.6}
         * @verifies{math-7.11}
         */
        CPPUNIT_TEST(test_inverse);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_DCM();
        void test_Euler_to_DCM();
        void test_multiply_vector();
        void test_transpose();
        void test_inverse();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(DCM_ut);

} // namespace

#endif // __MATH_DCM_UT_H__
