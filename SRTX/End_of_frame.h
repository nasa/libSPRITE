#ifndef __SRTX_END_OF_FRAME_H__
#define __SRTX_END_OF_FRAME_H__

#include "SRTX/Task.h"

namespace SRTX {

    /* This task gets scheduled as the lowest priority task in the rategroup.
     * When it executes to signals the scheduler that the rategroup completed
     * execution and stores the time at which it completed.
     */
    class End_of_frame : public Task {
      public:
        /**
         * Constructor.
         * @param name The name of the task.
         * @param finsihed Boolean flag use to indicate if the task ran
         * this frame.
         * @param end_time Returns the time at which the task executed.
         * This is used by the scheduler to determine how long the
         * rategroup took to complete execution.
         */
        End_of_frame(const char *const name, bool &finished,
                     units::Nanoseconds &end_time, Syncpoint &rategroup_sync)
            : Task(name)
            , m_finished(finished)
            , m_end_time(end_time)
            , m_rategroup_sync(rategroup_sync)
        {
            m_is_eof_task = true;
        }

        /**
         * Overriden method to begin task execution.
         * @return true if successful, else false.
         */
        bool start();

        /**
         * Overridden task execute method.
         * @return true on success or false on failure.
         */
        bool execute();

      private:
        /**
         * Flag that indicates that this task executed and by extension,
         * the rategroup completed execution.
         */
        bool &m_finished;

        /**
         * Time value stored by this task to indicate at what time the
         * rategroup completed execution.
         */
        units::Nanoseconds &m_end_time;

        /**
         * Hold a reference to the rategroup syncpoint.
         */
        Syncpoint &m_rategroup_sync;
    };
}

#endif //__SRTX_END_OF_FRAME_H__
