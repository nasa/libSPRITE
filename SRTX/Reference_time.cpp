
#include "SRTX/Reference_time.h"
#include "SRTX/Scheduler.h"

namespace SRTX {

    Reference_time::Reference_time() : m_value(units::Nanoseconds(0))
    {
    }

    units::Nanoseconds Reference_time::get_time()
    {
        // static Scheduler& s = Scheduler::get_instance();

        /* The scheduler is the one that updates time, so lock out the
         * scheduler when we're trying to get time.
         * TODO I don't think this is really the right solution. We need to
         * think on this. This class shouldn't really need to know about the
         * scheduler, and nothing prevents time from being updated by someone
         * other than the scheduler. I don't think putting a mutex in this
         * class is correct either, becuase what we're trying to prevent is
         * having a process read reference time between the time at which the
         * scheduler updated it, and the pending processes got released.
         * Perhaps the right answer is to make reference time an integral part
         * of the scheduler...
         */
        // s.lock();
        units::Nanoseconds time = m_value;
        // s.unlock();

        return time;
    }

    units::Nanoseconds get_reference_time()
    {
        static Reference_time &t = Reference_time::get_instance();

        return t.get_time();
    }

} // namespace
