// $Id$

#ifndef __MATH_DCM_UT_H__
#define __MATH_DCM_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace math
{
    class DCM_ut : public CppUnit::TestFixture
    {

    CPPUNIT_TEST_SUITE(DCM_ut);

    CPPUNIT_TEST(test_DCM);
    CPPUNIT_TEST(test_Euler_to_DCM);
    CPPUNIT_TEST(test_multiply_vector);
    CPPUNIT_TEST(test_transpose);
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
