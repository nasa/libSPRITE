#ifndef __UTIL_SAMPLE_SET_UT_H__
#define __UTIL_SAMPLE_SET_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace util
{

    class Sample_set_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Sample_set_ut);

        CPPUNIT_TEST(test_int);
        CPPUNIT_TEST(test_double);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_int();
        void test_double();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Sample_set_ut);

} //namespace

#endif // __UTIL_SAMPLE_SET_UT_H__
