#ifndef __UNITS_KILOMETERS_H__
#define __UNITS_KILOMETERS_H__

#include "base/types.h"
#include "units/Feet.h"
#include "units/Miles.h"
#include "units/Meters.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Meters;
    class Feet;
    class Miles;

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
        explicit Kilometers(const Meters &n);
        explicit Kilometers(const Feet &n);
        explicit Kilometers(const Miles &n);

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
