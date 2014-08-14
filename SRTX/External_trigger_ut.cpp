#include <unistd.h>
#include "base/types.h"
#include "base/XPRINTF.h"
#include "External_trigger_ut.h"
#include "Scheduler.h"
#include "Reference_time.h"
#include "RTC.h"

namespace SRTX
{

    namespace
    {
        units::Nanoseconds sched_period(10 * units::MSEC);
        const unsigned int NUM_PROCS = 101;
        int counter[NUM_PROCS];

        const priority_t highest_priority = MAX_PRIO - 1;
        const priority_t higher_priority = highest_priority - 1;
        const priority_t lower_priority = higher_priority - 1;
        const priority_t lowest_priority = lower_priority - 1;
        bool task_terminated;
    }


    /* This is the test task that we are going to run.
     */
    class Test_task : public Task
    {
        public:

            /**
             * Constructor.
             * @param name The name of the task.
             * @param i The task instances number.
             */
            Test_task(const char* const name, int i)
                : Task(name),
                m_instance(i)
        {
        }

            bool execute()
            {
                units::Nanoseconds period = get_period();

                ++counter[m_instance];
                DPRINTF("Running task %d with period %lld\n",
                        m_instance, (int64_t)period);

                /* If this is a aperiodic task (period is 0), sleep for a
                 * second.
                 */
                if(0 == period)
                {
                    sleep(units::Nanoseconds(1 * units::SEC));
                }

                return true;
            }

            void terminate()
            {
                task_terminated = true;
            }

        private:
            int m_instance;
    };


    void External_trigger_ut::setUp()
    {
        IPRINTF("Test using an external trigger for the scheduler.\n");
        memset(counter, 0, sizeof(counter));
    }


    void External_trigger_ut::tearDown()
    {
        IPRINTF("Completed testing an external trigger for the scheduler.\n");
    }


    void External_trigger_ut::test_trigger()
    {
        Task_db::value_t task_props;
        Scheduler& sched = Scheduler::get_instance();
        Reference_time& rtime = Reference_time::get_instance();

        /* Stop the scheduler if it is already running.
         */
        sched.stop();

        /* Set the scheduler to use an external trigger.
         */
        sched.use_external_trigger(true);

        /* Store the task properties.
         */
        task_props.period = sched_period;

        CPPUNIT_ASSERT_EQUAL(true, sched.set_properties(task_props));

        /* Now that the properties are set, try starting the task.
         */
        CPPUNIT_ASSERT_EQUAL(true, sched.start());

        /* Make sure the scheduler has had time to initialize.
         */
        sleep(units::Nanoseconds(0.1 * units::SEC));

        units::Nanoseconds time = rtime.get_time();
        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());
        time += sched_period;
        CPPUNIT_ASSERT_EQUAL(true, sched.trigger());
        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());

        sleep(units::Nanoseconds(0.1 * units::SEC));

        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());
        time += sched_period;
        CPPUNIT_ASSERT_EQUAL(true, sched.trigger());
        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());

        //sleep(units::Nanoseconds(0.1 * units::SEC));
        //IPRINTF("Reference time is %ld\n", uint64_t(rtime.get_time()));

        sched.stop();
        //IPRINTF("Reference time is %ld\n", uint64_t(rtime.get_time()));
#if 0
        /* The scheduler should start out running schedule 0.
         */
        CPPUNIT_ASSERT_EQUAL((schedule_t) 0, sched.get_schedule());
#endif
    }


#if 0
    void External_trigger_ut::test_tasks()
    {
        /* Create the tasks.
         */
        Task_properties tprops;
        tprops.period = units::Nanoseconds(20 * units::MSEC);
        tprops.prio = higher_priority;
        Test_task task1("task_2_1", 1);
        CPPUNIT_ASSERT_EQUAL(true, task1.set_properties(tprops));
        CPPUNIT_ASSERT_EQUAL(true, task1.is_valid());

        tprops.prio = lower_priority;
        Test_task task2("task_2_2", 2);
        CPPUNIT_ASSERT_EQUAL(true, task2.set_properties(tprops));
        CPPUNIT_ASSERT_EQUAL(true, task2.is_valid());

        tprops.period = units::Nanoseconds(10 * units::MSEC);
        tprops.prio = highest_priority;
        Test_task task3("task_1_3", 3);
        CPPUNIT_ASSERT_EQUAL(true, task3.set_properties(tprops));
        CPPUNIT_ASSERT_EQUAL(true, task3.is_valid());

        tprops.period = units::Nanoseconds(40 * units::MSEC);
        tprops.prio = lowest_priority;
        Test_task task4("task_4_4", 4);
        CPPUNIT_ASSERT_EQUAL(true, task4.set_properties(tprops));
        CPPUNIT_ASSERT_EQUAL(true, task4.is_valid());

        /* Set up this task with invalid period (faster than the scheduler).
         */
        tprops.period = units::Nanoseconds(sched_period / 2);
        tprops.prio = lowest_priority;
        Test_task task5("task_invalid_period", 5);
        CPPUNIT_ASSERT_EQUAL(true, task5.set_properties(tprops));
        CPPUNIT_ASSERT_EQUAL(true, task5.is_valid());

        /* Runtimes should be zero before the task starts.
         */
        units::Nanoseconds last_runtime = task1.get_last_runtime();
        CPPUNIT_ASSERT_EQUAL(units::Nanoseconds(0), last_runtime);
        CPPUNIT_ASSERT_EQUAL(units::Nanoseconds(0), task1.get_max_runtime());

        /* Off to the races.
         */
        task_terminated = false;
        CPPUNIT_ASSERT_EQUAL(true, task1.start());
        CPPUNIT_ASSERT_EQUAL(true, task2.start());
        CPPUNIT_ASSERT_EQUAL(true, task3.start());
        CPPUNIT_ASSERT_EQUAL(true, task4.start());

        IPRINTF("\nTesting invalid period, an error is expected\n");
        CPPUNIT_ASSERT_EQUAL(false, task5.start());

        /* Not the most reliable timing method.
         */
        sleep(units::Nanoseconds(1 * units::SEC));

        /* Stop the tasks so the counters stop incrementing. This makes
         * cleanup faster too.
         */
        DPRINTF("Halting all test tasks\n");
        DPRINTF("Stopping task 1\n");
        task1.stop();
        DPRINTF("Stopping task 2\n");
        task2.stop();
        DPRINTF("Stopping task 3\n");
        task3.stop();
        DPRINTF("Stopping task 4\n");
        task4.stop();
        CPPUNIT_ASSERT_EQUAL(true, task_terminated);

        /* Check the counters to see if the counts match. Allow some variance
         * to account for the imprecision of halting the task based on a
         * timer.
         */
        CPPUNIT_ASSERT((counter[1] >= 48) && (counter[1] <= 60));
        CPPUNIT_ASSERT((counter[2] >= 48) && (counter[2] <= 60));
        CPPUNIT_ASSERT((counter[3] >= 98) && (counter[3] <= 110));
        CPPUNIT_ASSERT((counter[4] >= 23) && (counter[4] <= 35));

        /* Check that the runtimes are reasonable.
         */
        last_runtime = task1.get_last_runtime();
        IPRINTF("last_runtime = %"PRId64"\n",int64_t (last_runtime));
        CPPUNIT_ASSERT (last_runtime > units::Nanoseconds(0));
        CPPUNIT_ASSERT (task1.get_max_runtime() >= last_runtime);
    }


    void External_trigger_ut::test_aperiodic_task()
    {
        const units::Nanoseconds test_delay(3 * units::SEC);
        IPRINTF("\nTesting aperiodic tasks. "
                "This test takes at least %"PRId64" seconds\n",
                int64_t(test_delay / units::SEC));

        /* Create an aperiodic task and make sure it is valid.
         */
        Task_properties task1_props;
        task1_props.prio = higher_priority;
        Test_task task1("aperiodic_1", 5);
        CPPUNIT_ASSERT_EQUAL(true, task1.set_properties(task1_props));
        CPPUNIT_ASSERT_EQUAL(true, task1.is_valid());

        /* Off to the races.
         */
        CPPUNIT_ASSERT_EQUAL(true, task1.start());

        /* Not the most reliable timing method.
         */
        sleep(test_delay);

        /* Check the counters to see if the counts match.
         */
        CPPUNIT_ASSERT_EQUAL(3, counter[5]);
    }
#endif

} // namespace
