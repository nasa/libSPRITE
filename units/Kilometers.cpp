#include "units/Meters.h"
#include "units/Kilometers.h"

namespace units {

    Kilometers::Kilometers(const Meters &n) : m_value(double(n.toKilometers()))
    {
    }

    units::Meters Kilometers::toMeters() const
    {
        return Meters(m_value * 1000);
    }

} // namespace
