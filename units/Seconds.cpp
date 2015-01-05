#include "units/Days.h"
#include "units/Nanoseconds.h"
#include "units/Seconds.h"


namespace units
{

    Seconds::Seconds(const Nanoseconds& n)
    {
        *this = n.toSeconds();
    }

    Seconds::Seconds(const Days& n)
    {
        *this = n.toSeconds();
    }

    Nanoseconds Seconds::toNanoseconds() const
    {
        return Nanoseconds(static_cast<int64_t>(m_value * 1000000000));
    }

    Days Seconds::toDays() const
    {
        return Days(m_value / SECONDS_PER_DAY);
    }

} // namespace
