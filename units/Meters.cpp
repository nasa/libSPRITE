#include "units/Meters.h"
#include "units/Feet.h"
#include "units/Miles.h"
#include "units/Kilometers.h"

namespace units
{

    Meters::Meters(const Kilometers& n)
    {
        *this = n.toMeters();
    }

    Meters::Meters(const Feet& n)
    {
        *this = n.toMeters();
    }

    Meters::Meters(const Miles& n)
    {
        *this = n.toFeet().toMeters();
    }

    units::Kilometers Meters::toKilometers() const
    {
        return Kilometers(m_value * .001);
    }

    units::Feet Meters::toFeet() const
    {
        return Feet(m_value * 1250 / 381);
    }

#if 0
    units::Miles Meters::toMiles() const
    {
        return n.toFeet().toMiles();
    }
#endif

} // namespace
