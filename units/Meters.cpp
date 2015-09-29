#include "units/Meters.h"
#include "units/Kilometers.h"
#include "units/Millimeters.h"

namespace units {

    Meters::Meters(const Kilometers &n) : m_value(double(n.toMeters()))
    {
    }

    units::Kilometers Meters::toKilometers() const
    {
        return Kilometers(m_value * .001);
    }

    Meters::Meters(const Millimeters &n) : m_value(double(n.toMeters()))
    {
    }

    units::Millimeters Meters::toMillimeters() const
    {
        return Millimeters(m_value * 1000);
    }

} // namespace
