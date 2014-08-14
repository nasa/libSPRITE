#ifndef __SRTX_SCHEDULER_UT_H__
#define __SRTX_SCHEDULER_UT_H__

#include <cppunit/extensions/HelperMacros.h>


namespace SRTX
{
    /**
     * Provide a number of tests for task scheduling.
     * @verify{@req{1114}}
     * @verify{@req{1115}}
     * @verify{@req{1116}}
     * @verify{@req{1118}}
     * @verify{@req{1119}}
     * @verify{@req{1123}}
     * @verify{@req{1124}}
     * @verify{@req{1228}}
     */
    class Scheduler_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Scheduler_ut);

        CPPUNIT_TEST(test_scheduler);
        CPPUNIT_TEST(test_tasks);
        CPPUNIT_TEST(test_overrun);
        CPPUNIT_TEST(test_aperiodic_task);
        CPPUNIT_TEST(test_many_tasks);
        CPPUNIT_TEST(test_schedules);

        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:

        /**
         * This test verifies some the of basic mechanics of the scheduler.
         * @verify{@req{1115}}
         */
        void test_scheduler();

        /**
         * This test verifies some the of basic mechanics of the scheduler.
         * @verify{@req{1228}}
         * @todo We don't have a way to receive notification of an overrun back
         * to the application yet, so we don't have a assertion to verify it.
         * Only a print statement. Once a notification mechanism is added, add
         * an assertion.
         */
        void test_overrun();

        /**
         * This routine tests periodic tasks.
         * @verify{@req{1114}}
         * @verify{@req{1115}}
         */
        void test_tasks();

        /**
         * This routine tests aperiodic tasks.
         * @verify{@req{1116}}
         */
        void test_aperiodic_task();

        /**
         * This routine tests many proccesses executing simultaneously at
         * various rates.
         * @verify{@req{1123}}
         * @verify{@req{1124}}
         */
        void test_many_tasks();

        /**
         * This routine tests the ability to set and query schedules from
         * the scheduler.
         * @verify{@req{1127}}
         */
        void test_schedules();

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Scheduler_ut);

} // namespace

#endif // __SRTX_SCHEDULER_UT_H__
