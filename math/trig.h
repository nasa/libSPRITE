// $Id$

#ifndef __MATH_TRIG_H__
#define __MATH_TRIG_H__

#include <math.h>
#include "units/Degrees.h"
#include "units/Radians.h"

namespace math
{

    double sin(const units::Radians& r);

    double sin(const units::Degrees& d);

    double cos(const units::Radians& r);

    double cos(const units::Degrees& d);

    double tan(const units::Radians& r);

    double tan(const units::Degrees& d);

    units::Radians asin2(double x);

    units::Radians acos2(double x);

    units::Radians atan2(double y, double x);

} // namespace

#endif // __MATH_TRIG_H__
