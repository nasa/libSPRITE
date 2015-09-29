#ifndef __UNITS_RADIANSPERSECOND_H__
#define __UNITS_RADIANSPERSECOND_H__

#include "base/types.h"

namespace units {

    /**
     * Define Radians/second as a unit of angular velocity.
     */
    class Radianspersecond {
      public:
        /**
         * Constructor.
         * @param v Number of tesla.
         * @satisfies{units-14.1}
         * @satisfies{units-14.2}
         * @satisfies{units-14.4}
         */
        explicit Radianspersecond(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Type conversion to double.
         * @satisfies{units-14.3}
         */
        operator double() const
        {
            return m_value;
        }

      private:
        /**
         * Stored value.
         */
        double m_value;
    };

} // namespace

#endif // __UNITS_RADIANSPERSECOND_H__
