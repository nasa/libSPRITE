#ifndef __UNITS_J2010_TIME_H__
#define __UNITS_J2010_TIME_H__

#include "units/Days.h"
#include "units/Seconds.h"

namespace units
{

    /**
     * Forward declaration of class.
     */
    class GPS_time;
    class J2000_time;

    class J2010_time : public Days
    {
        public:

            /**
             * Constructor.
             */
            explicit J2010_time(double n = 0) :
                Days(n)
            {
            }


            /**
             * Constructor.
             */
            explicit J2010_time(const Days& n) :
                Days(n)
            {
            }


            /**
             * Constructor.
             */
            explicit J2010_time(const GPS_time& n);


            /**
             * Constructor.
             */
            explicit J2010_time(const J2000_time& n);


            /**
             * Type conversion from J2010 epoch to J2000 time.
             * @return Time with respect to the J2000 epoch and format.
             */
            J2000_time toJ2000_time() const;


            /**
             * Type conversion from J2010 epoch to GPS time.
             * @return Time with respect to the GPS epoch and format.
             */
            GPS_time toGPS_time() const;

    };

    const int J2010_GPS_WEEK = 1564;
    const Seconds J2010_GPS_SECONDS = Seconds(432015.0);

} // namespace

#endif // __UNITS_J2010_TIME_H__
