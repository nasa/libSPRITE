#ifndef __UNITS_MILES_H__
#define __UNITS_MILES_H__

#include "base/types.h"
#include "units/Feet.h"
#include "units/Kilometers.h"
#include "units/Meters.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Kilometers;
    class Meters;
    class Feet;

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
        explicit Miles(const Kilometers &n);
        explicit Miles(const Meters &n);
        explicit Miles(const Feet &n);

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
