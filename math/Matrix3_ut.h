#ifndef __MATH_MATRIX3_UT_H__
#define __MATH_MATRIX3_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace math {
    class Matrix3_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Matrix3_ut);

        /**
         * @verifies{math-5.1}
         * @verifies{math-5.3}
         */
        CPPUNIT_TEST(test_Matrix3);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         */
        CPPUNIT_TEST(test_Matrix3_init);

        /**
         * @verifies{math-5.7}
         */
        CPPUNIT_TEST(test_equal);

        /**
         * @verifies{math-5.8}
         */
        CPPUNIT_TEST(test_not_equal);

        /**
         * @verifies{math-5.1}
         * @verifies{math-5.3}
         */
        CPPUNIT_TEST(test_get_set);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_add_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_subtract_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_multiply_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_divide_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_add_equal_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_subtract_equal_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_multiply_equal_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.4}
         */
        CPPUNIT_TEST(test_divide_equal_scalar);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.5}
         */
        CPPUNIT_TEST(test_add_matrix);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.5}
         */
        CPPUNIT_TEST(test_substract_matrix);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.5}
         */
        CPPUNIT_TEST(test_add_equal_matrix);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.5}
         */
        CPPUNIT_TEST(test_subtract_equal_matrix);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.5}
         */
        CPPUNIT_TEST(test_multiply_matrix);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.5}
         */
        CPPUNIT_TEST(test_multiply_equal_matrix);

        /**
         * @verifies{math-4.2}
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.9}
         */
        CPPUNIT_TEST(test_multiply_vector);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.10}
         */
        CPPUNIT_TEST(test_transpose);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.11}
         * @verifies{math-5.12}
         */
        CPPUNIT_TEST(test_inverse);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.12}
         */
        CPPUNIT_TEST(test_determinant);

        /**
         * @verifies{math-5.2}
         * @verifies{math-5.3}
         * @verifies{math-5.13}
         */
        CPPUNIT_TEST(test_trace);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_Matrix3();
        void test_Matrix3_init();
        void test_equal();
        void test_not_equal();
        void test_get_set();
        void test_add_scalar();
        void test_subtract_scalar();
        void test_multiply_scalar();
        void test_divide_scalar();
        void test_add_equal_scalar();
        void test_subtract_equal_scalar();
        void test_multiply_equal_scalar();
        void test_divide_equal_scalar();
        void test_add_matrix();
        void test_substract_matrix();
        void test_add_equal_matrix();
        void test_subtract_equal_matrix();
        void test_multiply_matrix();
        void test_multiply_equal_matrix();
        void test_multiply_vector();
        void test_transpose();
        void test_inverse();
        void test_determinant();
        void test_trace();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Matrix3_ut);

} // namespace

#endif // __MATH_MATRIX3_UT_H__
