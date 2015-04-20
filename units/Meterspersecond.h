#ifndef __UNITS_METERSPERSECOND_H__
#define __UNITS_METERSPERSECOND_H__

#include <math.h>
#include "base/types.h"

namespace units
{

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
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            Meterspersecond& operator+=(const Meterspersecond& rhs)
            {
                m_value += rhs.m_value;

                return *this;
            }


            /**
             * Overload operator-=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value subtracted.
             */
            Meterspersecond& operator-=(const Meterspersecond& rhs)
            {
                m_value -= rhs.m_value;

                return *this;
            }

        private:

            /**
             * Stored value.
             */
            double m_value;
    };

} // namespace

#endif // __UNITS_METERSPERSECOND_H__
