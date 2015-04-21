#ifndef __UNITS_J2000_TIME_H__
#define __UNITS_J2000_TIME_H__

#include "units/Days.h"
#include "units/Seconds.h"

namespace units
{

    /**
     * Forward declaration of class.
     */
    class GPS_time;
    class J2010_time;

    class J2000_time : public Days
    {
        public:

            /**
             * Constructor.
             */
            explicit J2000_time(double n = 0) :
                Days(n)
        {
        }


            /**
             * Constructor.
             */
            explicit J2000_time(const Days& n) :
                Days(n)
        {
        }


            /**
             * Constructor.
             */
            explicit J2000_time(const J2010_time& n);


            /**
             * Constructor.
             */
            explicit J2000_time(const GPS_time& n);


            /**
             * Type conversion from J2000 epoch to J2010 time.
             * @return Time with respect to the J2010 epoch and format.
             */
            J2010_time toJ2010_time() const;


            /**
             * Type conversion from J2000 epoch to GPS time.
             * @return Time with respect to the GPS epoch and format.
             */
            GPS_time toGPS_time() const;

    };

#if 0
    // @todo Fix these values.
    const int J2000_GPS_WEEK = 1564;
    const Seconds J2000_GPS_SECONDS = Seconds(432015.0);
#endif

} // namespace

#endif // __UNITS_J2000_TIME_H__
