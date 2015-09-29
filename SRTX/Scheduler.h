
#ifndef __SRTX_SCHEDULER_H__
#define __SRTX_SCHEDULER_H__

#include "SRTX/Task.h"
#include "SRTX/Syncpoint.h"

namespace SRTX {

    /**
     * Forward declare the implementation details of the scheduler
     * (PIMPL pattern).
     */
    struct Scheduler_impl;

    /**
     * This is the basic executive that schedules task.
     */
    class Scheduler : public Task {
      public:
        /**
         * There is a single instance of the scheduler in a given domain.
         * @return A reference to the domain's scheduler.
         */
        static Scheduler &get_instance();

        /**
         * Add a task to the scheduler.
         * @param p The task to be scheduled.
         * @return The syncronization condition variable released by the
         * scheduler when the task gets released by the scheduler on
         * success or NULL on failure.
         */
        Syncpoint *add_task(Task &p);

        /**
         * Remove a task from the scheduler.
         */
        void remove_task(Task &p);

        /**
         * Begin task execution.
         * @return true if successful, else false.
         */
        bool start();

        /**
         * Overriden method to begin task execution.
         * @return true on success or false on failure.
         */
        bool execute();

        /**
         * Block the scheduler from running.
         * @return true on success or false on failure.
         */
        bool lock();

        /**
         * Unblock the scheduler.
         * @return true on success or false on failure.
         */
        bool unlock();

        /**
         * Set a schedule for the scheduler.
         * The scheduler allows for sets of schedules in which differring
         * sets of tasks are set to run according to thier schedule
         * mask. This function changes the schedule.
         * @param s The schedule we want to change to.
         */
        void set_schedule(const schedule_t s)
        {
            m_schedule = s;
        }

        /**
         * Return the schedule.
         * The scheduler allows for sets of schedules in which differring
         * sets of tasks are set to run according to thier schedule
         * mask. This retreives the current schedule.
         * @return The current schedule.
         */
        schedule_t get_schedule() const
        {
            return m_schedule;
        }

        /**
         * Control whether the scheduler is slaved to an external trigger.
         * @param slave True to control through an external source else
         * false.
         */
        void use_external_trigger(bool slave);

        /**
         * Trigger the scheduler to release.
         * Applies when the scheduler is set to be triggered by an external
         * source.
         * @return True on success or false on failure.
         */
        bool trigger(void);

        /**
         * Routine invoked when the task is stopped.
         * Overriden task method which is executed when this task is stopped.
         */
        void terminate();

      private:
        /**
         * Constructor.
         * The constructor is made private as part of the singleton pattern.
         */
        Scheduler();

        /**
         * Copy constructor.
         * The copy constructor is made private as part of the singleton
         * pattern.
         */
        Scheduler(const Scheduler &);

        /**
         * Assignment operator.
         * The assignment operator is made private as part of the singleton
         * pattern.
         */
        Scheduler &operator=(const Scheduler &);

        /**
         * List of internal scheduler items. (PIMPL pattern).
         */
        Scheduler_impl *m_sched_impl;

        /**
         * The current schedule.
         */
        schedule_t m_schedule;

        /**
         * Flag used to indicate if we are slaved to an external time
         * source.
         */
        bool m_use_external_clock;

        /**
         * Instance of the Scheduler singleton.
         */
        static Scheduler *m_instance;
    };

} // namespace

#endif // __SRTX_SCHEDULER_H__
