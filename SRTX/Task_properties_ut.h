#ifndef __SRTX_TASK_PROPERTIES_UT_H__
#define __SRTX_TASK_PROPERTIES_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SRTX {
    /**
     * Provide tests for the configurable properties of a task.
     */
    class Task_properties_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Task_properties_ut);

        CPPUNIT_TEST(test_get_priority);
        CPPUNIT_TEST(test_get_period);
        CPPUNIT_TEST(test_get_schedule_presence);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_get_priority();
        void test_get_period();
        void test_get_schedule_presence();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Task_properties_ut);

} // namespace

#endif // __SRTX_TASK_PROPERTIES_UT_H__
