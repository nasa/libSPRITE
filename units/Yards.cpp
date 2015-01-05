#include "units/Yards.h"

namespace units
{

    Yards::Yards(const Centimeters& n)
    {
        *this = n.toMeters().toFeet().toYards();
    }

    Yards::Yards(const Meters& n)
    {
        *this = n.toFeet().toYards();
    }

    Yards::Yards(const Kilometers& n)
    {
        *this = n.toMeters().toFeet().toYards();
    }

    Yards::Yards(const Feet& n)
    {
        *this = n.toYards();
    }

    Yards::Yards(const Miles& n)
    {
        *this = n.toFeet().toYards();
    }

    units::Feet  Yards::toFeet() const
    {
        return Feet(m_value * 3);
    }

} // namespace
