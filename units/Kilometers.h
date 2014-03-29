#ifndef __UNITS_KILOMETERS_H__
#define __UNITS_KILOMETERS_H__

#include "base/types.h"
#include "Feet.h"
#include "Miles.h"
#include "Yards.h"
#include "Meters.h"
#include "Centimeters.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Centimeters;
    class Meters;
    class Feet;
    class Miles;
    class Yards;

    class Kilometers
    {
        public:

            /**
             * Constructor.
             * @param v Number of Kilometers.
             */
            explicit Kilometers(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Kilometers(const Centimeters& n);
            explicit Kilometers(const Meters& n);
            explicit Kilometers(const Feet& n);
            explicit Kilometers(const Miles& n);
            explicit Kilometers(const Yards& n);


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Type conversion from KiloMeters to Meters.
             * @return Kilometers value conversion to Meters.
             */
            units::Meters toMeters() const;

        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_KILOMETERS_H__
