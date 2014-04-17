// $Id$

#ifndef __SRTX_RTC_H__
#define __SRTX_RTC_H__

#include "units/Nanoseconds.h"


namespace SRTX
{

    /**
     * Get time from the system clock.
     * @param time Returned time in nanoseconds.
     * @return True on success or false on failure.
     * @satisfy{@req{1200}}
     */
    bool get_time(units::Nanoseconds& time);

    /**
     * Sleep for the specified number of nanoseconds.
     * @param time Number of nanoseconds to sleep.
     * @return True on success or false on failure. Errno is set on error.
     * @satisfy{@req{1199}}
     */
    bool sleep(const units::Nanoseconds& time);

} // namespace

#endif // __SRTX_RTC_H__
