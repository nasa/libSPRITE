#include <pthread.h>
#include "base/types.h"
#include "SRTX/Mutex_ut.h"
#include "Scheduler.h"
#include "Reference_time.h"
#include "RTC.h"

namespace SRTX {

    namespace {
        units::Nanoseconds sched_period(10 * units::MSEC);
    }

    void Mutex_ut::setUp()
    {
        Scheduler &sched = Scheduler::get_instance();
        Task_db::value_t task_props;

        task_props.period = sched_period;
        if(false == sched.set_properties(task_props)) {
            EPRINTF("Error setting scheduler properties\n");
            return;
        }

        /* Set the scheduler to use an external trigger.
         */
        //sched.use_external_trigger(true);
        if(false == sched.start()) {
            EPRINTF("Error starting the scheduler\n");
            return;
        }

        /* Make sure the scheduler has had time to initialize.
         */
        sleep(units::Nanoseconds(0.1 * units::SEC));
    }

    void Mutex_ut::tearDown()
    {
        Scheduler &sched = Scheduler::get_instance();
        sched.stop();
    }

    void Mutex_ut::test_mutex_no_contention()
    {
        Mutex m;

        CPPUNIT_ASSERT_EQUAL(true, m.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, m.lock());
        CPPUNIT_ASSERT_EQUAL(true, m.unlock());
    }

    void Mutex_ut::test_mutex_second_to_lock()
    {
        Mutex m;
        pthread_t thread;
        Reference_time &rtime = Reference_time::get_instance();

        CPPUNIT_ASSERT_EQUAL(true, m.is_valid());

        /* Create a thread that will lock our mutex for 1 second
         */
        int rc = pthread_create(&thread, NULL, Mutex_ut::lock_mutex_sleep_1_sec, (void*) &m);
        CPPUNIT_ASSERT_EQUAL(0, rc);

        /* Save the time before our current thread attempts to lock
         */
        units::Nanoseconds pre_lock_time = rtime.get_time();

        /* Make sure the competing thread locks first
         */
        sleep(units::Nanoseconds(0.5* units::SEC));

        /* Now we get the lock ourselves. Save the time
         */
        CPPUNIT_ASSERT_EQUAL(true, m.lock());
        units::Nanoseconds post_lock_time = rtime.get_time();
        CPPUNIT_ASSERT_EQUAL(true, m.unlock());

        /* One second should have passed
         * due to the periodic nature of the scheduler's update of Reference_time, give it some leeway (.2s)
         */
        CPPUNIT_ASSERT_EQUAL(true, post_lock_time > pre_lock_time + .8 * units::Nanoseconds(units::SEC));
    }

    void Mutex_ut::test_mutex_first_to_lock()
    {
        Mutex m;
        pthread_t thread;
        pthread_attr_t thread_attr;
        Reference_time &rtime = Reference_time::get_instance();
        void *status;

        /* Lock the mutex right here
         */
        CPPUNIT_ASSERT_EQUAL(true, m.lock());

        /* Create a joinable thread that will lock our mutex for 1 second
         */
        pthread_attr_init(&thread_attr);
        pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_JOINABLE);
        int rc = pthread_create(&thread, &thread_attr, Mutex_ut::lock_mutex_sleep_1_sec, (void*) &m);

        /* no RAII to help us here -- clean up thread_attr before making any assertions
         */
        pthread_attr_destroy(&thread_attr);
        CPPUNIT_ASSERT_EQUAL(0, rc);

        /* Save the current time before we release the lock
         */
        units::Nanoseconds pre_thread_exit_time = rtime.get_time();

        /* Sleep one second before our new thread gets the lock
         */
        sleep(units::Nanoseconds(units::SEC));
        CPPUNIT_ASSERT_EQUAL(true, m.unlock());

        /* Now that the lock is released, the thread should sleep 1 second before it joins.
         */
        rc = pthread_join(thread, &status);
        CPPUNIT_ASSERT_EQUAL(0, rc);

        /* Two seconds should have passed
         * due to the periodic nature of the scheduler's update of Reference_time, give it some leeway (.2s)
         */
        units::Nanoseconds post_thread_exit_time = rtime.get_time();
        CPPUNIT_ASSERT_EQUAL(true, post_thread_exit_time > pre_thread_exit_time + units::Nanoseconds(1.8 * units::SEC));
    }

    void *Mutex_ut::lock_mutex_sleep_1_sec(void *mutex_ptr)
    {
        Mutex& m = *(Mutex*) mutex_ptr;
        CPPUNIT_ASSERT_EQUAL(true, m.is_valid());

        /* Lock
         */
        CPPUNIT_ASSERT_EQUAL(true, m.lock());

        /* Sleep
         */
        sleep(units::Nanoseconds(units::SEC));

        /* Unlock & exit
         */
        CPPUNIT_ASSERT_EQUAL(true, m.unlock());
        pthread_exit(NULL);
    }

} // namespace
