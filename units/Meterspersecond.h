#ifndef __UNITS_METERSPERSECOND_H__
#define __UNITS_METERSPERSECOND_H__

#include <math.h>
#include "base/types.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Kilometersperhour;
    class Feetpersecond;
    class Milesperhour;

    class Meterspersecond
    {
        public:

            /**
             * Constructor.
             * @param v Number of Meterspersecond.
             */
            explicit Meterspersecond(double v = 0.0)
            {
                m_value = (fabs(v) > NEAR_ZERO) ? v : 0;
            }

            /**
             * Constructor.
             */
            explicit Meterspersecond(const Kilometersperhour& n);
            explicit Meterspersecond(const Feetpersecond& n);
            explicit Meterspersecond(const Milesperhour& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from Meterspersecond to Kilometersperhour.
             */
            units::Kilometersperhour toKilometersperhour() const;

            /**
             * Type conversion from Meterspersecond to Feetpersecond.
             */
            units::Feetpersecond toFeetpersecond() const;

        private:

            /**
             * Stored value.
             */
            double m_value;
    };

} // namespace

#endif // __UNITS_METERSPERSECOND_H__
