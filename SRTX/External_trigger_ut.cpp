#include <unistd.h>
#include "base/types.h"
#include "base/XPRINTF.h"
#include "External_trigger_ut.h"
#include "Scheduler.h"
#include "Reference_time.h"
#include "RTC.h"

namespace SRTX {

    namespace {
        units::Nanoseconds sched_period(10 * units::MSEC);
    }

    void External_trigger_ut::setUp()
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
        sched.use_external_trigger(true);
        if(false == sched.start()) {
            EPRINTF("Error starting the scheduler\n");
            return;
        }

        /* Make sure the scheduler has had time to initialize.
         */
        sleep(units::Nanoseconds(0.1 * units::SEC));
    }

    void External_trigger_ut::tearDown()
    {
        Scheduler &sched = Scheduler::get_instance();
        sched.stop();
    }

    void External_trigger_ut::test_trigger()
    {
        IPRINTF("\nStarting %s\n", __func__);

        Scheduler &sched = Scheduler::get_instance();
        Task_db::value_t task_props;
        Reference_time &rtime = Reference_time::get_instance();

        units::Nanoseconds time = rtime.get_time();
        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());

        /* Make sure time increments with each trigger.
         */
        CPPUNIT_ASSERT_EQUAL(true, sched.trigger());
        time += sched_period;
        sleep(units::Nanoseconds(0.1 * units::SEC));
        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());

        CPPUNIT_ASSERT_EQUAL(true, sched.trigger());
        time += sched_period;
        sleep(units::Nanoseconds(0.1 * units::SEC));
        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());

        /* Let things run for a second. Time shouldn't change because there have
         * been no trigger events.
         */
        sleep(units::SEC);
        CPPUNIT_ASSERT_EQUAL(time, rtime.get_time());

        IPRINTF("Completed %s\n", __func__);
    }

} // namespace
