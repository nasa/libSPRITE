#ifndef __MATH_TRIG_UT_H__
#define __MATH_TRIG_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace math {
    class trig_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(trig_ut);

        /**
         * @verifies{math-1.1}
         * @verifies{math-2.1}
         */
        CPPUNIT_TEST(test_sin);

        /**
         * @verifies{math-1.2}
         * @verifies{math-2.2}
         */
        CPPUNIT_TEST(test_cos);

        /**
         * @verifies{math-1.3}
         * @verifies{math-2.3}
         */
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
