#ifndef __MATH_MATRIX3_UT_H__
#define __MATH_MATRIX3_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace math
{
    class Matrix3_ut : public CppUnit::TestFixture
    {

    CPPUNIT_TEST_SUITE(Matrix3_ut);

    CPPUNIT_TEST(test_Matrix3);
    CPPUNIT_TEST(test_Matrix3_init);
    CPPUNIT_TEST(test_Matrix3_init_array);
    CPPUNIT_TEST(test_equal);
    CPPUNIT_TEST(test_not_equal);
    CPPUNIT_TEST(test_get_set);
    CPPUNIT_TEST(test_add_scalar);
    CPPUNIT_TEST(test_subtract_scalar);
    CPPUNIT_TEST(test_multiply_scalar);
    CPPUNIT_TEST(test_divide_scalar);
    CPPUNIT_TEST(test_add_equal_scalar);
    CPPUNIT_TEST(test_subtract_equal_scalar);
    CPPUNIT_TEST(test_multiply_equal_scalar);
    CPPUNIT_TEST(test_divide_equal_scalar);
    CPPUNIT_TEST(test_add_matrix);
    CPPUNIT_TEST(test_substract_matrix);
    CPPUNIT_TEST(test_add_equal_matrix);
    CPPUNIT_TEST(test_subtract_equal_matrix);
    CPPUNIT_TEST(test_multiply_matrix);
    CPPUNIT_TEST(test_multiply_equal_matrix);
    CPPUNIT_TEST(test_multiply_vector);
    CPPUNIT_TEST(test_transpose);
    CPPUNIT_TEST(test_inverse);
    CPPUNIT_TEST(test_determinant);
    CPPUNIT_TEST(test_trace);

    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

    protected:
        void test_Matrix3();
        void test_Matrix3_init();
        void test_Matrix3_init_array();
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
