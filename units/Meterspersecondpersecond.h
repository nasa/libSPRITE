#ifndef __UNITS_METERSPERSECONDPERSECOND_H__
#define __UNITS_METERSPERSECONDPERSECOND_H__

#include "base/types.h"

namespace units {

    class Meterspersecondpersecond {
      public:
        /**
         * Constructor.
         * @param v Number of Meterspersecondpersecond.
         * @satisfies{units-10.1}
         * @satisfies{units-10.2}
         * @satisfies{units-10.4}
         */
        explicit Meterspersecondpersecond(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Type conversion to double.
         * @satisfies{units-10.3}
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
         * @satisfies{units-10.5}
         */
        Meterspersecondpersecond &
        operator+=(const Meterspersecondpersecond &rhs)
        {
            m_value += rhs.m_value;

            return *this;
        }

        /**
         * Overload operator-=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value subtracted.
         * @satisfies{units-10.5}
         */
        Meterspersecondpersecond &
        operator-=(const Meterspersecondpersecond &rhs)
        {
            m_value -= rhs.m_value;

            return *this;
        }

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_METERSPERSECONDPERSECOND_H__
