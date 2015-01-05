#include "units/Miles.h"

namespace units
{

    Miles::Miles(const Kilometers& n)
    {
        *this = n.toMeters().toFeet().toMiles();
    }

    Miles::Miles(const Meters& n)
    {
        *this = n.toFeet().toMiles();
    }

    Miles::Miles(const Feet& n)
    {
        *this = n.toMiles();
    }

    units::Feet  Miles::toFeet() const
    {
        return Feet(m_value * 5280);
    }

} // namespace
