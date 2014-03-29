#ifndef __UNITS_GALLONS_H__
#define __UNITS_GALLONS_H__

#include "base/types.h"
#include "Liters.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Liters;

    class Gallons
    {
        public:

            /**
             * Constructor.
             * @param v Number of Gallons.
             */
            explicit Gallons(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Gallons(const Liters& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from Gallons to Liters.
             */
            units::Liters toLiters() const;


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_GALLONS_H__
