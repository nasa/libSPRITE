#include "units/Feet.h"

namespace units
{

    Feet::Feet(const Kilometers& n)
    {
        *this = n.toMeters().toFeet();
    }

    Feet::Feet(const Meters& n)
    {
        *this = n.toFeet();
    }

    Feet::Feet(const Miles& n)
    {
        *this = n.toFeet();
    }

    units::Miles  Feet::toMiles() const
    {
        return Miles(m_value / 5280);
    }

    units::Meters  Feet::toMeters() const
    {
        return Meters(m_value * 0.3048);
    }

} // namespace
