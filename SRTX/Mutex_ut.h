#ifndef __SRTX_MUTEX_UT_H__
#define __SRTX_MUTEX_UT_H__

#include <cppunit/extensions/HelperMacros.h>
#include "SRTX/Mutex.h"

namespace SRTX {
    class Mutex_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Mutex_ut);

        CPPUNIT_TEST(test_mutex_no_contention);
        CPPUNIT_TEST(test_mutex_second_to_lock);
        CPPUNIT_TEST(test_mutex_first_to_lock);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_mutex_no_contention();
        void test_mutex_second_to_lock();
        void test_mutex_first_to_lock();

        static void *lock_mutex_sleep_1_sec(void *mutex_ptr);

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Mutex_ut);

} // namespace

#endif // __SRTX_MUTEX_UT_H__
