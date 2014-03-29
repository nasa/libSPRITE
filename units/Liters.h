#ifndef __UNITS_LITERS_H__
#define __UNITS_LITERS_H__

#include "base/types.h"
#include "Gallons.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Gallons;

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
             * Constructor.
             */
            explicit Liters(const Gallons& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from Liters to Gallons.
             */
            units::Gallons toGallons() const;


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_LITERS_H__
