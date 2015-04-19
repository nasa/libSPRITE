#include "units/Days.h"
#include "units/GPS_time.h"

namespace units
{

    Days GPS_time::toDays() const
    {
        return Days(m_week * DAYS_PER_WEEK + Days(m_seconds));
    }

} // namespace
