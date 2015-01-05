#ifndef __COORD_GST_ANGLE_H__
#define __COORD_GST_ANGLE_H__

#include "units/J2000_time.h"
#include "units/Radians.h"


namespace coord
{

    /**
     * Calculate the apparent Greenwich Sidreal Time.
     * @param JD Julian date referenced to the USNO J2000 epoch.
     * @return Apparent angle from the prime meridian.
     */
    units::Radians calculate_GST_angle(const units::J2000_time& JD);

} // namespace

#endif // __COORD_GST_ANGLE_H__
