#include "SRTX/End_of_frame.h"
#include "SRTX/RTC.h"

namespace SRTX {

    bool End_of_frame::start()
    {
        /* If construction was not successful, don't bother trying to start.
         */
        if(false == m_valid) {
            EPRINTF("%s:Invalid task\n", m_name);
            return false;
        }

        /* Get the task attributes.
         */
        if(false == m_prop_symbol->entry->read(m_props)) {
            EPRINTF("%s:Failed to get task properties\n", m_name);
            return false;
        }

        if(false == start_prep()) {
            return false;
        }

        return spawn_thread();
    }

    bool End_of_frame::execute()
    {
        /* This is always the last task in a chain of periodic tasks, so when
         * this one starts trying to run, that means all tasks are ready to run
         * and they can all be released.
         */
        m_rategroup_sync.condition_cleared();
        m_rategroup_sync.release();

        DPRINTF("Executing End_of_frame task %s\n", m_name);

        get_time(m_end_time);
        m_finished = true;

        return true;
    }

} // end namespace
