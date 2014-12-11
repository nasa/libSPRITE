#include "coord/GST_angle.h"
#include "math/trig.h"
#include "units/J2000_time.h"
#include "units/J2010_time.h"


namespace coord
{

    units::Radians calculate_GST_angle(const units::J2000_time& JD)
    {
        /* See: http://aa.usno.navy.mil/faq/docs/GAST.php
         */
        const double D = JD;
        const units::Degrees omega(125.04 - 0.052954 * D);
        const units::Degrees L2((280.47 + 0.98565 * D) * 2);
        const units::Degrees epsilon(23.4393 - 0.0000004 * D);
        const double dPhi = -0.000319*math::sin(omega)-0.000024*math::sin(L2);
        const double GMST = fmod(18.697374558 + 24.06570982441908 * D, 24);
        const double GAST = GMST + dPhi*math::cos(epsilon);

        /* Convert from hours to radians and return.
         */
        return units::Radians(GAST*M_PI/12);
    }

}
