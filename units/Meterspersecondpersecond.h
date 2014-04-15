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
            explicit Meterspersecondpersecond(double v = 0.0)
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


            /**
             * Overload operator+
             * @param rhs Right hand side of the operation.
             * @return The added value
             */
            Meterspersecondpersecond operator+(const Meterspersecondpersecond& rhs) const
            {
                return Meterspersecondpersecond(m_value + rhs.m_value);
            }


            /**
             * Overload operator-
             * @param rhs Right hand side of the operation.
             * @return The subtracted value.
             */
            Meterspersecondpersecond operator-(const Meterspersecondpersecond& rhs) const
            {
                return Meterspersecondpersecond(m_value - rhs.m_value);
            }


            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            Meterspersecondpersecond& operator+=(const Meterspersecondpersecond& rhs)
            {
                m_value += rhs.m_value;

                return *this;
            }


            /**
             * Overload operator-=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value subtracted.
             */
            Meterspersecondpersecond& operator-=(const Meterspersecondpersecond& rhs)
            {
                m_value -= rhs.m_value;

                return *this;
            }


        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_METERSPERSECONDPERSECOND_H__
