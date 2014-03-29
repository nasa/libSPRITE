#include "Kilometers.h"

namespace units
{

    Kilometers::Kilometers(const Meters& n)
    {
        *this = n.toKilometers();
    }

    Kilometers::Kilometers(const Centimeters& n)
    {
        *this = n.toMeters().toKilometers();
    }

    Kilometers::Kilometers(const Feet& n)
    {
        *this = n.toMeters().toKilometers();
    }

    Kilometers::Kilometers(const Miles& n)
    {
        *this = n.toFeet().toMeters().toKilometers();
    }

    Kilometers::Kilometers(const Yards& n)
    {
        *this = n.toFeet().toMeters().toKilometers();
    }

    units::Meters  Kilometers::toMeters() const
    {
        return Meters(m_value * 1000);
    }

} // namespace
