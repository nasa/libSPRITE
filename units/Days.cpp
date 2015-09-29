#include "units/Days.h"
#include "units/Seconds.h"

namespace units {

    Days::Days(const Seconds &n) : m_value(double(n.toDays()))
    {
    }

    units::Seconds Days::toSeconds() const
    {
        return Seconds(m_value * SECONDS_PER_DAY);
    }

} // namespace
