#include "units/J2000_time.h"
#include "units/J2010_time.h"
#include "units/GPS_time.h"

namespace units
{

    J2000_time::J2000_time(const J2010_time &n)
    {
        *this = n.toJ2000_time();
    }

#if 0
    J2000_time::J2000_time(const GPS_time& n)
    {
        *this = n.toJ2000_time();
    }

    GPS_time J2000_time::toGPS_time() const
    {
        return GPS_time(J2000_GPS_WEEK, J2000_GPS_SECONDS) += Seconds(*this);
    }
#endif

    J2010_time J2000_time::toJ2010_time() const
    {
        return J2010_time(*this - 3652.5);
    }

} // namespace
