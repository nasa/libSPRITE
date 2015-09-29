#ifndef __UNITS_TESLA_H__
#define __UNITS_TESLA_H__

#include "base/types.h"

namespace units {

    /**
     * Define Tesla as a unit of magnetic flux.
     */
    class Tesla {
      public:
        /**
         * Constructor.
         * @param v Number of tesla.
         * @satisfies{units-16.1}
         * @satisfies{units-16.2}
         * @satisfies{units-16.4}
         */
        explicit Tesla(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Type conversion to double.
         * @satisfies{units-16.3}
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
