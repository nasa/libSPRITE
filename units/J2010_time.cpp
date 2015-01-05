#include "units/J2000_time.h"
#include "units/J2010_time.h"
#include "units/GPS_time.h"


namespace units
{

    J2010_time::J2010_time(const J2000_time& n)
    {
        *this = n.toJ2010_time();
    }

    J2010_time::J2010_time(const GPS_time& n)
    {
        *this = n.toJ2010_time();
    }

    J2000_time J2010_time::toJ2000_time() const
    {
        return J2000_time(*this + 3652.5);
    }

    GPS_time J2010_time::toGPS_time() const
    {
        return GPS_time(J2010_GPS_WEEK, J2010_GPS_SECONDS) += Seconds(*this);
    }

} // namespace
