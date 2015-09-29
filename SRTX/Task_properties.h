#ifndef __SRTX_TASK_PROPERTIES_H__
#define __SRTX_TASK_PROPERTIES_H__

#include "SRTX/Scheduler_types.h"
#include "units/Nanoseconds.h"

namespace SRTX {

    /**
     * This class defines the configurable properties of a task and
     * mechanisms to manipulate those properties.
     */
    class Task_properties {
      public:
        /**
         * Constructor.
         */
        Task_properties()
            : prio(0)
            , period(0)
            , schedule_presence(0xFFFFFFFF)
            , stack_size(0x1000000)
            , max_runtime(0)
            , last_runtime(0)
        {
        }

        /**
         * Is the task in the given schedule?
         * @param s Schedule to test.
         * @return True if the task is in the current schedule, else return
         * false.
         */
        bool is_present_in_schedule(unsigned int s) const
        {
            /* Return false if the parameter is out of range.
             */
            if(s > (sizeof(schedule_presence) * 8 - 1)) {
                return false;
            }

            return schedule_presence & (1 << s);
        }

        /**
         * Task priority.
         */
        priority_t prio;

        /**
         * Inidicate the periodic rate of a task in nanoseconds. 0 is
         * used to indicate an aperiodic task.
         */
        units::Nanoseconds period;

        /**
         * The system allows for a number of fixed schedules with varying
         * mixes of task.  This variable is used as a bit-mask indicating
         * whether the task is present in (1 << n) schedule.
         */
        schedule_presence_t schedule_presence;

        /**
         * The task stack size.
         */
        unsigned int stack_size;

        /**
         * The maximum amount of time it has ever taken for the task to
         * complete.
         */
        units::Nanoseconds max_runtime;

        /**
         * The amount of time it took for the most recent execution of the
         * task.
         */
        units::Nanoseconds last_runtime;
    };

    const unsigned int MIN_PRIO = sched_get_priority_min(SCHED_FIFO);
    const unsigned int MAX_PRIO = sched_get_priority_max(SCHED_FIFO);

} // namespace

#endif // __SRTX_TASK_PROPERTIES_H__
