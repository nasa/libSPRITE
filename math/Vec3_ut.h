#ifndef __MATH_VEC3_UT_H__
#define __MATH_VEC3_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace math {

    /**
     * Test three element vectors.
     */
    class Vec3_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Vec3_ut);

        /**
         * @verifies{math-4.1}
         * @verifies{math-4.3}
         */
        CPPUNIT_TEST(test_Vec3);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         */
        CPPUNIT_TEST(test_Vec3_init);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_add_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_subtract_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_multiply_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_divide_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_add_equal_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_subtract_equal_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_multiply_equal_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.4}
         */
        CPPUNIT_TEST(test_divide_equal_scalar);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.5}
         */
        CPPUNIT_TEST(test_add_vector);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.5}
         */
        CPPUNIT_TEST(test_subtract_vector);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.5}
         */
        CPPUNIT_TEST(test_add_equal_vector);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.3}
         * @verifies{math-4.5}
         */
        CPPUNIT_TEST(test_subtract_equal_vector);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.7}
         */
        CPPUNIT_TEST(test_magnitude_squared);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.6}
         */
        CPPUNIT_TEST(test_magnitude);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.6}
         * @verifies{math-4.8}
         */
        CPPUNIT_TEST(test_normalize);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.9}
         */
        CPPUNIT_TEST(test_dot);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.10}
         */
        CPPUNIT_TEST(test_cross);

        /**
         * @verifies{math-4.2}
         * @verifies{math-4.10}
         */
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
