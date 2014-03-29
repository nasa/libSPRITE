#include "Days.h"
#include "J2010_time.h"
#include "GPS_time.h"
#include "Seconds.h"

namespace units
{

    Days::Days(const Seconds& n)
    {
        *this = n.toDays();
    }

    Days::Days(const GPS_time& n)
    {
        *this = n.toDays();
    }

    units::Seconds Days::toSeconds() const
    {
        return Seconds(m_value * SECONDS_PER_DAY);
    }

} // namespace
