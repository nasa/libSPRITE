#include <unistd.h>
#include "base/types.h"
#include "base/XPRINTF.h"
#include "Scheduler_ut.h"
#include "Scheduler.h"
#include "RTC.h"
#include "Runtime_attributes.h"

namespace SRTX {

    namespace {
        units::Nanoseconds sched_period(10 * units::MSEC);
        const unsigned int NUM_PROCS = 101;
        int counter[NUM_PROCS];

        const priority_t highest_priority = MAX_PRIO - 1;
        const priority_t higher_priority = highest_priority - 1;
        const priority_t lower_priority = higher_priority - 1;
        const priority_t lowest_priority = lower_priority - 1;
        bool task_terminated;
    }

    /* This task will sleep during it's execute method to deliberatly cause an
     * overrun.
     */
    class Overrun_task : public Task {
      public:
        Overrun_task(const char *const name) : Task(name)
        {
        }

        bool execute()
        {
            sleep(units::Nanoseconds(100 * units::MSEC));
            return true;
        }
    };

    /* This is the test task that we are going to run.
     */
    class Test_task : public Task {
      public:
        /**
         * Constructor.
         * @param name The name of the task.
         * @param i The task instances number.
         */
        Test_task(const char *const name, int i, int run_count = 0)
            : Task(name)
            , m_instance(i)
            , m_run_count(run_count)
        {
        }

        bool execute()
        {
            units::Nanoseconds period = get_period();

            ++counter[m_instance];
            DPRINTF("Running task %d with period %lld\n", m_instance,
                    (int64_t)period);

            /* If this is a aperiodic task (period is 0), sleep for a
             * second.
             */
            if(0 == period) {
                sleep(units::Nanoseconds(1 * units::SEC));
                if(--m_run_count <= 0) {
                    return false;
                }
            }

            return true;
        }

        void terminate()
        {
            task_terminated = true;
        }

      private:
        int m_instance;
        int m_run_count;
    };

    void Scheduler_ut::setUp()
    {
        Scheduler &sched = Scheduler::get_instance();
        Task_db::value_t task_props;

        task_props.period = sched_period;
        if(false == sched.set_properties(task_props)) {
            EPRINTF("Error setting scheduler properties\n");
            return;
        }

        sched.use_external_trigger(false);
        if(false == sched.start()) {
            EPRINTF("Error starting the scheduler\n");
            return;
        }

        memset(counter, 0, sizeof(counter));
    }

    void Scheduler_ut::tearDown()
    {
        Scheduler &sched = Scheduler::get_instance();
        sched.stop();
    }

    void Scheduler_ut::test_scheduler()
    {
        IPRINTF("\nExecuting %s\n", __func__);
        Scheduler &sched = Scheduler::get_instance();

        /* The scheduler should start out running schedule 0.
         */
        CPPUNIT_ASSERT_EQUAL((schedule_t)0, sched.get_schedule());
    }

    void Scheduler_ut::test_overrun()
    {
        IPRINTF("\nExecuting %s\n", __func__);
        /* Create and run a task that deliberatly causes overruns.
         */
        Task_properties tp;
        tp.prio = 50;
        tp.period = units::Nanoseconds(50 * units::MSEC);
        Overrun_task t("overrun_task");
        CPPUNIT_ASSERT_EQUAL(true, t.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, t.set_properties(tp));

        IPRINTF("\nWe expect a task overrun here\n");
        CPPUNIT_ASSERT_EQUAL(true, t.start());

        /* Run for a little bit. Not the most reliable timing method.
         */
        sleep(units::Nanoseconds(1100 * units::MSEC));
        t.stop();

        /* Set up to read the runtime attributes for this rategroup.
         */
        Runtime_attributes_db &rt_db = Runtime_attributes_db::get_instance();
        Runtime_attributes_db::value_t rt_value;
        char sym_name[SYM_ENTRY_STRLEN + 1];
        snprintf(sym_name, SYM_ENTRY_STRLEN, "%s%" PRId64 "",
                 runtime_attr_symbol_prefix, int64_t(tp.period));
        Runtime_attributes_db::symbol_t *rt_symbol =
            rt_db.lookup_symbol(sym_name);

        /* Make sure that we found the symbol.
         */
        CPPUNIT_ASSERT(rt_symbol);

        /* We should have recorded some overruns.
         */
        CPPUNIT_ASSERT_EQUAL(true, rt_symbol->entry->read(rt_value));
        CPPUNIT_ASSERT(rt_value.max_runtime > tp.period);
#ifdef DEBUG_OVERRUN_BUG
        fprintf(stderr, "UT Num overruns = %u\n", rt_value.num_overruns);
        fprintf(stderr, "UT last runtime = %ld\n",
                int64_t(rt_value.last_runtime));
        fprintf(stderr, "UT max runtime = %ld\n",
                int64_t(rt_value.max_runtime));
#endif
        CPPUNIT_ASSERT(rt_value.num_overruns);
    }

    void Scheduler_ut::test_tasks()
    {
        IPRINTF("\nExecuting %s\n", __func__);
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
        IPRINTF("last_runtime = %" PRId64 "\n", int64_t(last_runtime));
        CPPUNIT_ASSERT(last_runtime > units::Nanoseconds(0));
        CPPUNIT_ASSERT(task1.get_max_runtime() >= last_runtime);
    }

    void Scheduler_ut::test_aperiodic_task()
    {
        IPRINTF("\nExecuting %s\n", __func__);
        const units::Nanoseconds test_delay(3 * units::SEC);
        IPRINTF("\nTesting aperiodic tasks. "
                "This test takes at least %" PRId64 " seconds\n",
                int64_t(test_delay / units::SEC));

        /* Create an aperiodic task and make sure it is valid.
         */
        Task_properties task1_props;
        task1_props.prio = higher_priority;
        Test_task task1("aperiodic_1", 5, 3);
        CPPUNIT_ASSERT_EQUAL(true, task1.set_properties(task1_props));
        CPPUNIT_ASSERT_EQUAL(true, task1.is_valid());

        /* Off to the races.
         */
        CPPUNIT_ASSERT_EQUAL(true, task1.start());

        /* Not the most reliable timing method.
         */
        sleep(test_delay);
        task1.stop();

        /* Check the counters to see if the counts match.
         */
        CPPUNIT_ASSERT_EQUAL(3, counter[5]);
    }

    void Scheduler_ut::test_many_tasks()
    {
        IPRINTF("\nExecuting %s\n", __func__);
        memset(counter, 0, sizeof(counter));

        Test_task *task[NUM_PROCS];

        for(unsigned int i = 0; i < NUM_PROCS; ++i) {
            Task_properties task_props;

            /* Allocate each task to one of 10 rate groups.
             */
            task_props.prio = 70 + (i % 10);
            task_props.period =
                (units::Nanoseconds((units::SEC) / ((i % 10) + 1)) /
                 sched_period) *
                sched_period;
            char task_name[20];
            sprintf(task_name, "mtask_%d", i);

            /* Create the tasks and make sure they're valid.
             */
            task[i] = new Test_task(task_name, i);
            CPPUNIT_ASSERT_EQUAL(true, task[i]->set_properties(task_props));
            CPPUNIT_ASSERT_EQUAL(true, task[i]->is_valid());
        }

        for(unsigned int i = 0; i < NUM_PROCS; ++i) {
            CPPUNIT_ASSERT_EQUAL(true, task[i]->start());
        }

        sleep(units::Nanoseconds(1 * units::SEC));

        for(unsigned int i = 0; i < NUM_PROCS; ++i) {
            /* Since each task should have run for a bit more than one
             * seconds its count should be greater than its frequency, but
             * probably not more than double that.
             */
            units::Nanoseconds period = task[i]->get_period();
            int ex = units::SEC / period;

            char msg[128];
            sprintf(msg,
                    "%s period %" PRId64 ", instance %d ex = %d, actual = %d",
                    task[i]->get_name(), (int64_t)period, i, ex, counter[i]);
            CPPUNIT_ASSERT_MESSAGE(msg, counter[i] >= ex);
            CPPUNIT_ASSERT_MESSAGE(msg, counter[i] < (2 * ex));
            task[i]->stop();
        }

        for(unsigned int i = 0; i < NUM_PROCS; ++i) {
            delete task[i];
        }
    }

    void Scheduler_ut::test_schedules()
    {
        IPRINTF("\nExecuting %s\n", __func__);
        Task_db::value_t task_props;
        Scheduler &sched = Scheduler::get_instance();
#if 0

        /* Halt the scheduler.
         */
        sched.stop();

        /* Store the task properties.
         */
        task_props.prio = 98;
        task_props.period = sched_period;

        CPPUNIT_ASSERT_EQUAL(true, sched.set_properties(task_props));
#endif

        CPPUNIT_ASSERT_EQUAL((unsigned)0, sched.get_schedule());

        for(schedule_t i = 0; i < 32; ++i) {
            sched.set_schedule(i);
            CPPUNIT_ASSERT_EQUAL(i, sched.get_schedule());
        }

        /* Create the tasks and make sure they're valid.
         */
        task_props.period = units::Nanoseconds(20 * units::MSEC);
        task_props.prio = higher_priority;
        task_props.schedule_presence = 0x000A; // 1010
        Test_task task1("task_1", 1);
        CPPUNIT_ASSERT_EQUAL(true, task1.set_properties(task_props));
        CPPUNIT_ASSERT_EQUAL(true, task1.is_valid());

        task_props.prio = lower_priority;
        task_props.schedule_presence = 0x000D; // 1101
        Test_task task2("task_2", 2);
        CPPUNIT_ASSERT_EQUAL(true, task2.set_properties(task_props));
        CPPUNIT_ASSERT_EQUAL(true, task2.is_valid());

        sched.set_schedule(31);

        /* Off to the races.
         */
        CPPUNIT_ASSERT_EQUAL(true, task1.start());
        CPPUNIT_ASSERT_EQUAL(true, task2.start());
        // CPPUNIT_ASSERT_EQUAL(true, sched.start());

        IPRINTF("\nTesting multiple schedules.\n"
                "This test will take at least 4 seconds to complete.\n");
        for(int i = 0; i < 4; ++i) {
            sched.set_schedule(i);

            /* Not the most reliable timing method.
             */
            sleep(units::Nanoseconds(1 * units::SEC));

            sched.set_schedule(31);

            /* Check the counters to see if the counts match. Allow some
             * variance to account for the imprecision of halting the task
             * based on a timer.
             */
            if(task1.is_present_in_schedule(i)) {
                CPPUNIT_ASSERT((counter[1] >= 48) && (counter[1] <= 60));
            } else {
                CPPUNIT_ASSERT_EQUAL(0, counter[1]);
            }

            if(task2.is_present_in_schedule(i)) {
                CPPUNIT_ASSERT((counter[2] >= 48) && (counter[2] <= 60));
            } else {
                CPPUNIT_ASSERT_EQUAL(0, counter[2]);
            }

            counter[1] = 0;
            counter[2] = 0;
        }

        DPRINTF("Halting all test tasks\n");
        DPRINTF("Stopping task 1\n");
        task1.stop();
        DPRINTF("Stopping task 2\n");
        task2.stop();

        sched.set_schedule(0);
        CPPUNIT_ASSERT_EQUAL((unsigned)0, sched.get_schedule());
    }

} // namespace
