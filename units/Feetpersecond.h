#ifndef __UNITS_FEETPERSECOND_H__
#define __UNITS_FEETPERSECOND_H__

#include "base/types.h"
#include "Milesperhour.h"
#include "Kilometersperhour.h"
#include "Meterspersecond.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Kilometersperhour;
    class Meterspersecond;
    class Milesperhour;

    class Feetpersecond
    {
        public:

            /**
             * Constructor.
             * @param v Number of Feetpersecond.
             */
            explicit Feetpersecond(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Feetpersecond(const Kilometersperhour& n);
            explicit Feetpersecond(const Meterspersecond& n);
            explicit Feetpersecond(const Milesperhour& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from Feetpersecond to Milesperhour.
             */
            units::Milesperhour toMilesperhour() const;

            /**
             * Type conversion from Feetpersecond to Meterspersecond.
             */
            units::Meterspersecond toMeterspersecond() const;


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_FEETPERSECOND_H__
