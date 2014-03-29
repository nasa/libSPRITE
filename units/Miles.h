#ifndef __UNITS_MILES_H__
#define __UNITS_MILES_H__

#include "base/types.h"
#include "Feet.h"
#include "Yards.h"
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
    class Yards;

    class Miles
    {
        public:

            /**
             * Constructor.
             * @param v Number of Miles.
             */
            explicit Miles(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Miles(const Centimeters& n);
            explicit Miles(const Kilometers& n);
            explicit Miles(const Meters& n);
            explicit Miles(const Feet& n);
            explicit Miles(const Yards& n);


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Type conversion from Miles to Feet.
             * @return Miles value conversion to Feet.
             */
            units::Feet toFeet() const;

        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_MILES_H__
