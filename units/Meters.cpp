#include "units/Meters.h"
#include "units/Kilometers.h"

namespace units
{

    Meters::Meters(const Kilometers& n)
    {
        *this = n.toMeters();
    }

    units::Kilometers Meters::toKilometers() const
    {
        return Kilometers(m_value * .001);
    }

} // namespace
