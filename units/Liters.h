#ifndef __UNITS_LITERS_H__
#define __UNITS_LITERS_H__

#include "base/types.h"

namespace units
{
    class Liters
    {
        public:

            /**
             * Constructor.
             * @param v Number of Liters.
             */
            explicit Liters(double v)
                : m_value(v)
            {
            }


            /**
             * Type conversion to double.
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
