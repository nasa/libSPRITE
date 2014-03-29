#ifndef __UNITS_FEET_H__
#define __UNITS_FEET_H__

#include "base/types.h"
#include "Miles.h"
#include "Yards.h"
#include "Kilometers.h"
#include "Meters.h"
#include "Centimeters.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Kilometers;
    class Meters;
    class Centimeters;
    class Miles;
    class Yards;

    class Feet
    {
        public:

            /**
             * Constructor.
             * @param v Number of seconds.
             */
            explicit Feet(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Feet(const Kilometers& n);
            explicit Feet(const Centimeters& n);
            explicit Feet(const Meters& n);
            explicit Feet(const Miles& n);
            explicit Feet(const Yards& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Type conversion from Feet to Miles.
             */
            units::Miles toMiles() const;

            /**
             * Type conversion from Feet to Yards.
             */
            units::Yards toYards() const;

            /**
             * Type conversion from Feet to Meters.
             */
            units::Meters toMeters() const;


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_FEET_H__
