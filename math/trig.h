#ifndef __MATH_TRIG_H__
#define __MATH_TRIG_H__

#include <math.h>
#include "units/Degrees.h"
#include "units/Radians.h"

namespace math {

    /**
     * @satisfies{math-1.1}
     */
    double sin(const units::Radians &r);

    /**
     * @satisfies{math-2.1}
     */
    double sin(const units::Degrees &d);

    /**
     * @satisfies{math-1.2}
     */
    double cos(const units::Radians &r);

    /**
     * @satisfies{math-2.2}
     */
    double cos(const units::Degrees &d);

    /**
     * @satisfies{math-1.3}
     */
    double tan(const units::Radians &r);

    /**
     * @satisfies{math-2.3}
     */
    double tan(const units::Degrees &d);

    /**
     * @satisfies{math-3.1}
     */
    units::Radians asin2(double x);

    /**
     * @satisfies{math-3.2}
     */
    units::Radians acos2(double x);

    /**
     * @satisfies{math-3.3}
     */
    units::Radians atan2(double y, double x);

} // namespace

#endif // __MATH_TRIG_H__
