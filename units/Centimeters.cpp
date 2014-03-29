#include "Centimeters.h"

namespace units
{

    Centimeters::Centimeters(const Kilometers& n)
    {
        *this = (n.toMeters()).toCentimeters();
    }

    Centimeters::Centimeters(const Meters& n)
    {
        *this = n.toCentimeters();
    }

    Centimeters::Centimeters(const Feet& n)
    {
        *this = n.toMeters().toCentimeters();
    }

    Centimeters::Centimeters(const Yards& n)
    {
        *this = n.toFeet().toMeters().toCentimeters();
    }

    Centimeters::Centimeters(const Miles& n)
    {
        *this = n.toFeet().toMeters().toCentimeters();
    }

    units::Meters  Centimeters::toMeters() const
    {
        return Meters(m_value * .01);
    }

} // namespace
