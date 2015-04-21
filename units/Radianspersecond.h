#ifndef __UNITS_RADIANSPERSECOND_H__
#define __UNITS_RADIANSPERSECOND_H__

#include "base/types.h"

namespace units
{

    /**
     * Define Radians/second as a unit of angular velocity.
     */
    class Radianspersecond
    {
      public:
        /**
         * Constructor.
         * @param v Number of tesla.
         */
        explicit Radianspersecond(double v = 0.0)
        {
            m_value = (fabs(v) > NEAR_ZERO) ? v : 0;
        }

        /**
         * Type conversion to double.
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
