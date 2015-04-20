#ifndef __UNITS_METERSPERSECONDPERSECOND_H__
#define __UNITS_METERSPERSECONDPERSECOND_H__

#include "base/types.h"

namespace units
{

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
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

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
