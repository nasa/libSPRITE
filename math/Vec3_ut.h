/*******************************************************************************
 * $Id$
 */

#ifndef __MATH_VEC3_UT_H__
#define __MATH_VEC3_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace math
{

    /**
     * Test three element vectors.
     * @verify{@req{1253}}
     */
    class Vec3_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Vec3_ut);

        CPPUNIT_TEST(test_Vec3);
        CPPUNIT_TEST(test_Vec3_init);
        CPPUNIT_TEST(test_add_scalar);
        CPPUNIT_TEST(test_subtract_scalar);
        CPPUNIT_TEST(test_multiply_scalar);
        CPPUNIT_TEST(test_divide_scalar);
        CPPUNIT_TEST(test_add_equal_scalar);
        CPPUNIT_TEST(test_subtract_equal_scalar);
        CPPUNIT_TEST(test_multiply_equal_scalar);
        CPPUNIT_TEST(test_divide_equal_scalar);
        CPPUNIT_TEST(test_add_vector);
        CPPUNIT_TEST(test_subtract_vector);
        CPPUNIT_TEST(test_add_equal_vector);
        CPPUNIT_TEST(test_subtract_equal_vector);
        CPPUNIT_TEST(test_magnitude_squared);
        CPPUNIT_TEST(test_magnitude);
        CPPUNIT_TEST(test_normalize);
        CPPUNIT_TEST(test_dot);
        CPPUNIT_TEST(test_cross);
        CPPUNIT_TEST(test_cross_cast);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_Vec3();
        void test_Vec3_init();
        void test_add_scalar();
        void test_subtract_scalar();
        void test_multiply_scalar();
        void test_divide_scalar();
        void test_add_equal_scalar();
        void test_subtract_equal_scalar();
        void test_multiply_equal_scalar();
        void test_divide_equal_scalar();
        void test_add_vector();
        void test_subtract_vector();
        void test_add_equal_vector();
        void test_subtract_equal_vector();
        void test_magnitude_squared();
        void test_magnitude();
        void test_normalize();
        void test_dot();
        void test_cross();
        void test_cross_cast();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Vec3_ut);

} // namespace

#endif // __MATH_VEC3_UT_H__
