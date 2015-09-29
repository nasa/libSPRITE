#ifndef __UNITS_KILOMETERS_H__
#define __UNITS_KILOMETERS_H__

#include "base/types.h"

namespace units {

    /**
     * Forward declaration of class.
     */
    class Meters;

    class Kilometers {
      public:
        /**
         * Constructor.
         * @param v Number of Kilometers.
         * @satisfies{units-6.1}
         * @satisfies{units-6.2}
         * @satisfies{units-6.4}
         */
        explicit Kilometers(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Constructor.
         * @satisfies{units-6.6}
         */
        explicit Kilometers(const Meters &n);

        /**
         * Type conversion to double.
         * @satisfies{units-6.3}
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Type conversion from KiloMeters to Meters.
         * @return Kilometers value conversion to Meters.
         * @satisfies{units-6.6}
         */
        units::Meters toMeters() const;

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_KILOMETERS_H__
