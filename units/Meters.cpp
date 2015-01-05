#include "units/Meters.h"
#include "units/Feet.h"
#include "units/Miles.h"
#include "units/Yards.h"
#include "units/Kilometers.h"
#include "units/Centimeters.h"

namespace units
{

    Meters::Meters(const Kilometers& n)
    {
        *this = n.toMeters();
    }

    Meters::Meters(const Centimeters& n)
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

    Meters::Meters(const Yards& n)
    {
        *this = n.toFeet().toMeters();
    }

    units::Kilometers Meters::toKilometers() const
    {
        return Kilometers(m_value * .001);
    }

    units::Centimeters Meters::toCentimeters() const
    {
        return Centimeters(m_value * 100);
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

    units::Yards Meters::toYards() const
    {
        return n.toFeet().toYards();
    }
#endif

} // namespace
