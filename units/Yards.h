#ifndef __UNITS_YARDS_H__
#define __UNITS_YARDS_H__

#include "base/types.h"
#include "Feet.h"
#include "Miles.h"
#include "Kilometers.h"
#include "Meters.h"
#include "Centimeters.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Centimeters;
    class Kilometers;
    class Meters;
    class Feet;
    class Miles;

    class Yards
    {
        public:

            /**
             * Constructor.
             * @param v Number of Yards.
             */
            explicit Yards(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Yards(const Centimeters& n);
            explicit Yards(const Kilometers& n);
            explicit Yards(const Meters& n);
            explicit Yards(const Feet& n);
            explicit Yards(const Miles& n);


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Type conversion from Yards to Feet.
             * @return Yards value conversion to Feet.
             */
            units::Feet toFeet() const;

        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_YARDS_H__
