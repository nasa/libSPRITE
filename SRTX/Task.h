#ifndef __SRTX_TASK_H__
#define __SRTX_TASK_H__

#include "SRTX/Symbol_db.h"
#include "SRTX/Task_properties.h"


namespace SRTX
{

    /**
     * Define a task database type that contains the task properties.
     */
    typedef Symbol_db<Task_properties> Task_db;


    /**
     * Forward declare the implementation details of a task (PIMPL pattern).
     */
    struct Task_impl;


    /**
     * A task is the basic unit that gets scheduled in the systems.
     * @satisfy{@req{1115}}
     * @satisfy{@req{1116}}
     * @satisfy{@req{1117}}
     * @satisfy{@req{1118}}
     */
    class Task
    {
        public:

            /**
             * Constructor.
             * @param name Name that will be used to reference the task and
             * under which the task properties will be stored in the symbol
             * table.
             */
            Task(const char* name);

            /**
             * Did the task get validly constructed?
             * @return true if validly constructed, else false.
             */
            bool is_valid() const
            {
                return m_valid;
            }

            /**
             * Set the task properties.
             * @param props Task properties.
             * @return True on success or false on failure.
             */
            bool set_properties(const Task_db::value_t& props);

            /**
             * Is the task in it's operational state.
             * A task is operational if it was validly constructed and has
             * been started (and not been stopped).
             * @return true if operational, else false.
             */
            bool is_operational() const
            {
                return m_operational;
            }

            /**
             * Get the task name.
             * @return task name.
             */
            const char* get_name() const
            {
                return m_name;
            }

            /**
             * Get the period at which the task is to be scheduled.
             * @return The taskes period.
             */
            units::Nanoseconds get_period() const
            {
                return m_props.period;
            }

            /**
             * Begin task execution.
             * @return true if successful, else false.
             */
            bool start();

            /**
             * Stop the execution of a task.
             * @return true if successful, else false.
             */
            void stop();

            /**
             * This is the function that a task runs when invoked by the
             * scheduler.
             * The application is expected to override this method when they
             * derive thier class.
             * @return true on success or false on failure.
             */
            virtual bool execute()
            {
                return true;
            }

            /**
             * Get the task's priority.
             * @return The task priority.
             */
            priority_t get_priority() const;

            /**
             * Test is see if this task is in a given schedule.
             * @param s Schedule id.
             * @return True if in schedule s, else false.
             */
            bool is_present_in_schedule(unsigned int s) const;

            units::Nanoseconds get_max_runtime() const;

            units::Nanoseconds get_last_runtime() const;

            /**
             * Destructor.
             */
            virtual ~Task();

            /**
             * Task initialization routine.
             * This method may be overriden by a derived task class. It is
             * invoked by the when start() is called.
             */
            virtual bool init()
            {
                return m_valid;
            }

            /**
             * Task termination.
             * This method may be overriden by a derived task class. It is
             * invoked by the when stop() is called.
             */
            virtual void terminate()
            {
                return;
            }

        protected:

            /**
             * Prepare the task to be started.
             * This function is only called by a start() function that
             * overloads the default task start() function.
             */
            bool start_prep();

            /**
             * Spwan a task thread.
             * This function is only called by a start() function that
             * overloads the default task start() function.
             */
            bool spawn_thread();

            /**
             * The task properties from the task database.
             */
            Task_db::value_t m_props;

            /**
             * Entry for the task properties in the task database.
             */
            Task_db::symbol_t* m_prop_symbol;

            /**
             * Boolean indicating whether the task has been validly
             * constructed.
             */
            bool m_valid;

            /**
             * Boolean indicating whether the task is in it's operational
             * state.
             */
            volatile bool m_operational;

            /**
             * Task name.
             * Add one for the NUL string terminator.
             */
            const char* m_name;

        private:

            /**
             * This is the task entry point.
             */
            static void* run(void* arg);

            /**
             * Pointer to the specific implementatipon of a task.
             * (PIMPL pattern).
             */
            Task_impl* m_impl;

    };

} // namespace

#endif // __SRTX_TASK_H__
