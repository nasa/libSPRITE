#ifndef __UNITS_FEETPERSECONDPERSECOND_H__
#define __UNITS_FEETPERSECONDPERSECOND_H__

#include "base/types.h"
#include "Meterspersecondpersecond.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Meterspersecondpersecond;

    class Feetpersecondpersecond
    {
        public:

            /**
             * Constructor.
             * @param v Number of Feetpersecondpersecond.
             */
            explicit Feetpersecondpersecond(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Feetpersecondpersecond(const Meterspersecondpersecond& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from Feetpersecondpersecond to Meterspersecondpersecond.
             */
            units::Meterspersecondpersecond toMeterspersecondpersecond() const;


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_FEETPERSECONDPERSECOND_H__
