#include "units/Millimeters.h"
#include "units/Meters.h"

namespace units {

    Millimeters::Millimeters(const Meters &m)
        : m_value(int64_t(m.toMillimeters()))
    {
    }

    units::Meters Millimeters::toMeters() const
    {
        return Meters(m_value / 1000.0);
    }

} // namespace
