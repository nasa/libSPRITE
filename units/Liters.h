#ifndef __UNITS_LITERS_H__
#define __UNITS_LITERS_H__

#include "base/types.h"

namespace units {
    class Liters {
      public:
        /**
         * Constructor.
         * @param v Number of Liters.
         * @satisfies{units-7.1}
         * @satisfies{units-7.2}
         * @satisfies{units-7.4}
         */
        explicit Liters(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Type conversion to double.
         * @satisfies{units-7.3}
         */
        operator double() const
        {
            return m_value;
        }

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_LITERS_H__
