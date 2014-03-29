#ifndef __UNITS_METERS_H__
#define __UNITS_METERS_H__

#include <math.h>
#include "base/types.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Kilometers;
    class Centimeters;
    class Feet;
    class Miles;
    class Yards;

    class Meters
    {
        public:

            /**
             * Constructor.
             * @param v Number of seconds.
             */
            explicit Meters(double v = 0.0)
            {
                m_value = (fabs(v) > NEAR_ZERO) ? v : 0;
            }

            /**
             * Constructor.
             */
            explicit Meters(const Kilometers& n);
            explicit Meters(const Centimeters& n);
            explicit Meters(const Feet& n);
            explicit Meters(const Miles& n);
            explicit Meters(const Yards& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from Meters to Kilometers.
             */
            units::Kilometers toKilometers() const;

            /**
             * Type conversion from Meters to Centimeters.
             */
            units::Centimeters toCentimeters() const;

            /**
             * Type conversion from Meters to Feet.
             */
            units::Feet toFeet() const;

#if 0
            /**
             * Type conversion from Meters to Miles.
             */
            units::Miles toMiles() const;

            /**
             * Type conversion from Meters to Yards.
             */
            units::Yards toYards() const;
#endif

        private:

            /**
             * Stored value.
             */
            double m_value;

    };

} // namespace

#endif // __UNITS_METERS_H__
