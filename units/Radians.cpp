#include <math.h>
#include "units/Degrees.h"
#include "units/Radians.h"

namespace units {

    Radians::Radians(const Degrees &d) : m_value(double(d.toRadians()))
    {
    }

    Degrees Radians::toDegrees() const
    {
        return Degrees(m_value * 180 / M_PI);
    }

} // namespace
