#include <math.h>
#include "units/Degrees.h"
#include "units/Radians.h"

namespace units
{

    Degrees::Degrees(const Radians &r)
    {
        *this = r.toDegrees();
    }

    Radians Degrees::toRadians() const
    {
        return Radians(m_value * M_PI / 180);
    }

} // namespace
