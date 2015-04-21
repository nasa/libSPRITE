#ifndef __UNITS_FEET_H__
#define __UNITS_FEET_H__

#include "base/types.h"
#include "units/Miles.h"
#include "units/Kilometers.h"
#include "units/Meters.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Kilometers;
    class Meters;
    class Miles;

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
            explicit Feet(const Meters& n);
            explicit Feet(const Miles& n);

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
             * Type conversion from Feet to Meters.
             */
            units::Meters toMeters() const;


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_FEET_H__
