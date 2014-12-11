#ifndef __SRTX_MUTEX_UT_H__
#define __SRTX_MUTEX_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace SRTX
{
    class Mutex_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Mutex_ut);

        CPPUNIT_TEST(test_mutex);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_mutex();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Mutex_ut);

} // namespace

#endif // __SRTX_MUTEX_UT_H__
