#ifndef __UNITS_CENTIMETERS_H__
#define __UNITS_CENTIMETERS_H__

#include "base/types.h"
#include "Feet.h"
#include "Miles.h"
#include "Yards.h"
#include "Kilometers.h"
#include "Meters.h"

namespace units
{


    /**
     * Forward declataration of class.
     */
    class Kilometers;
    class Meters;
    class Feet;
    class Miles;
    class Yards;

    class Centimeters
    {
        public:

            /**
             * Constructor.
             * @param v Number of Centimeters.
             */
            explicit Centimeters(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Centimeters(const Kilometers& n);
            explicit Centimeters(const Meters& n);
            explicit Centimeters(const Feet& n);
            explicit Centimeters(const Miles& n);
            explicit Centimeters(const Yards& n);


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Type conversion from Centimeters to Meters.
             * @return Centimeters value conversion to Meters.
             */
            units::Meters toMeters() const;

        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_CENTIMETERS_H__
