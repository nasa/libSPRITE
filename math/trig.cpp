#include <math.h>
#include "base/assertion.h"
#include "math/trig.h"

namespace math {

    double sin(const units::Radians &r)
    {
        return ::sin(r);
    }

    double sin(const units::Degrees &d)
    {
        return sin(units::Radians(d));
    }

    double cos(const units::Radians &r)
    {
        return ::cos(r);
    }

    double cos(const units::Degrees &d)
    {
        return cos(units::Radians(d));
    }

    double tan(const units::Radians &r)
    {
        /* The value of tan(pi/2) is infinite. Assert if someone tries to
         * calculate it.
         */
        assert(fabs(fmod(r, M_PI)) != M_PI / 2);

        return ::tan(r);
    }

    double tan(const units::Degrees &d)
    {
        return tan(units::Radians(d));
    }

    units::Radians asin2(double x)
    {
        /* Validate the input to asin to avoid NAN errors.
         */
        assert(fabs(x) <= 1);

        return units::Radians(::asin(x));
    }

    units::Radians acos2(double x)
    {
        /* Validate the input to acos to avoid NAN errors.
         */
        assert(fabs(x) <= 1);

        return units::Radians(::acos(x));
    }

    units::Radians atan2(double y, double x)
    {
        return units::Radians(::atan2(y, x));
    }

} // namespace
