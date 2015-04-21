#ifndef __UNITS_TESLA_H__
#define __UNITS_TESLA_H__

#include "base/types.h"

namespace units
{

    /**
     * Define Tesla as a unit of magnetic flux.
     */
    class Tesla
    {
      public:
        /**
         * Constructor.
         * @param v Number of tesla.
         */
        explicit Tesla(double v = 0.0)
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

#endif // __UNITS_TESLA_H__
