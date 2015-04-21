#include "units/Nanoseconds.h"
#include "units/Seconds.h"

namespace units
{

    Nanoseconds::Nanoseconds(const Seconds &s)
    {
        *this = s.toNanoseconds();
    }

    Seconds Nanoseconds::toSeconds() const
    {
        return Seconds(m_value / 1000000000.0);
    }

} // namespace
