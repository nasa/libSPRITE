#include <time.h>
#include "SRTX/RTC.h"
#include "base/XPRINTF.h"

namespace SRTX {

    bool get_time(units::Nanoseconds &time)
    {
        struct timespec ts;

        if(-1 == clock_gettime(CLOCK_REALTIME, &ts)) {
            PERROR("clock_gettime");
            return false;
        }

        time = units::Nanoseconds(ts.tv_sec * units::SEC + ts.tv_nsec);

        return true;
    }

    bool sleep(const units::Nanoseconds &time)
    {
        struct timespec ts;

        ts.tv_sec = time / units::SEC;
        ts.tv_nsec = time % units::SEC;

        return 0 == nanosleep(&ts, NULL);
    }

} // namespace
