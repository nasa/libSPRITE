#include "units/Gallons.h"

namespace units
{

    Gallons::Gallons(const Liters& n)
    {
        *this = n.toGallons();
    }


    units::Liters Gallons::toLiters() const
    {
        return Liters(m_value * 3.785411784);
    }


} // namespace
