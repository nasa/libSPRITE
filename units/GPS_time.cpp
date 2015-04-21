#include "units/Days.h"
#include "units/GPS_time.h"
#include "units/J2010_time.h"

namespace units
{

    GPS_time::GPS_time(const J2010_time &t)
    {
        *this = t.toGPS_time();
    }

    Days GPS_time::toDays() const
    {
        return Days(m_week * DAYS_PER_WEEK + Days(m_seconds));
    }

    J2010_time GPS_time::toJ2010_time() const
    {
        const GPS_time J2010_OFFSET(J2010_GPS_WEEK, J2010_GPS_SECONDS);
        return J2010_time(Days(*this - J2010_OFFSET));
    }

} // namespace
