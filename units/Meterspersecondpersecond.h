#ifndef __UNITS_METERSPERSECONDPERSECOND_H__
#define __UNITS_METERSPERSECONDPERSECOND_H__

#include "base/types.h"
#include "Feetpersecondpersecond.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Feetpersecondpersecond;

    class Meterspersecondpersecond
    {
        public:

            /**
             * Constructor.
             * @param v Number of Meterspersecondpersecond.
             */
            explicit Meterspersecondpersecond(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Meterspersecondpersecond(const Feetpersecondpersecond& n);

            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from Meterspersecondpersecond to Feetpersecondpersecond.
             */
            units::Feetpersecondpersecond toFeetpersecondpersecond() const;


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_METERSPERSECONDPERSECOND_H__
