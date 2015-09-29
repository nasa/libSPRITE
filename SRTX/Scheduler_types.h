#ifndef __SRTX_SCHEDULER_TYPES_H__
#define __SRTX_SCHEDULER_TYPES_H__

#include <pthread.h>
#include "base/types.h"

namespace SRTX {

    /**
     * Alias the native OS type for a mutex.
     */
    typedef pthread_mutex_t mutex_t;

    /**
     * Define the type that stores schedule presence.  The system allows for a
     * number of fixed schedules with varying mixes of process.  Values of this
     * type are used as a bit-mask indicating whether the process is present in
     * (1 << n) schedule.
     */
    typedef uint32_t schedule_presence_t;

    /**
     * Define a type for the processes attributes.
     * These are properties not presented to local scheduler. The definition of
     * this type is implementation dependent and intended to help hide the
     * underlying thread mechanism (in this case, pthreads).
     */
    typedef pthread_attr_t process_attr_t;

    /**
     * Define type for process priority.
     * This type is implementation dependent.
     */
    typedef unsigned int priority_t;

    /**
     * Define a type to represent schedules.
     */
    typedef uint32_t schedule_t;

} // namespace

#endif // __SRTX_SCHEDULER_TYPES_H__
