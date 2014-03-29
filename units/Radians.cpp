#include <math.h>
#include "Degrees.h"
#include "Radians.h"


namespace units
{

    Radians::Radians(const Degrees& d)
    {
        *this = d.toRadians();
    }

    Degrees Radians::toDegrees() const
    {
        return Degrees(m_value * 180 / M_PI);
    }

} // namespace
