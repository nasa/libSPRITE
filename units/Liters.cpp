#include "units/Liters.h"

namespace units
{

    Liters::Liters(const Gallons &n)
    {
        *this = n.toLiters();
    }

    units::Gallons Liters::toGallons() const
    {
        return Gallons(m_value / 3.785411784);
    }

} // namespace
