#include "units/Millimeters.h"
#include "units/Meters.h"

namespace units
{

    Millimeters::Millimeters(const Meters &m)
    {
        *this = m.toMillimeters();
    }

    units::Meters Millimeters::toMeters() const
    {
        return Meters(m_value / 1000.0);
    }

} // namespace
