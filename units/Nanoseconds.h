#ifndef __UNITS_NANOSECONDS_H__
#define __UNITS_NANOSECONDS_H__

#include "base/types.h"

namespace units {

    /**
     * Forward declaration of class.
     */
    class Seconds;

    class Nanoseconds {
      public:
        /**
         * Constructor.
         * @param v Number of nanoseconds.
         * @satisfies{units-11.1}
         * @satisfies{units-11.2}
         * @satisfies{units-11.4}
         */
        explicit Nanoseconds(int64_t v = 0) : m_value(v)
        {
        }

        /**
         * Constructor.
         * @satisfies{units-11.7}
         */
        explicit Nanoseconds(const Seconds &s);

        /**
         * Type conversion to a 64-bit integer.
         * @satisfies{units-11.3}
         * @satisfies{units-11.5}
         */
        operator int64_t() const
        {
            return m_value;
        }

        /**
         * Type conversion from nanoseconds to seconds.
         * @return nanoseconds value converted to seconds.
         * @satisfies{units-11.6}
         */
        Seconds toSeconds() const;

        /**
         * Overload operator+
         * @param rhs Right hand side of the operation.
         * @return The added value
         * @satisfies{units-11.5}
         */
        Nanoseconds operator+(const Nanoseconds &rhs) const
        {
            return Nanoseconds(m_value + rhs.m_value);
        }

        /**
         * Overload operator-
         * @param rhs Right hand side of the operation.
         * @return The subtracted value.
         * @satisfies{units-11.5}
         */
        Nanoseconds operator-(const Nanoseconds &rhs) const
        {
            return Nanoseconds(m_value - rhs.m_value);
        }

        /**
         * Overload operator*
         * @param rhs Right hand side of the operation.
         * @return The multiplied value.
         * @satisfies{units-11.5}
         */
        Nanoseconds operator*(const Nanoseconds &rhs) const
        {
            return Nanoseconds(m_value * rhs.m_value);
        }

        /**
         * Overload operator/
         * @param rhs Right hand side of the operation.
         * @return The divided value.
         * @satisfies{units-11.5}
         */
        Nanoseconds operator/(const Nanoseconds &rhs) const
        {
            return Nanoseconds(m_value / rhs.m_value);
        }

        /**
         * Overload operator%
         * @param rhs Right hand side of the operation.
         * @return The modulo value.
         * @satisfies{units-11.5}
         */
        Nanoseconds operator%(const Nanoseconds &rhs) const
        {
            return Nanoseconds(m_value % rhs.m_value);
        }

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
         * @satisfies{units-11.5}
         */
        Nanoseconds &operator+=(const Nanoseconds &rhs)
        {
            m_value += rhs.m_value;

            return *this;
        }

        /**
         * Overload operator-=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value subtracted.
         * @satisfies{units-11.5}
         */
        Nanoseconds &operator-=(const Nanoseconds &rhs)
        {
            m_value -= rhs.m_value;

            return *this;
        }

      private:
        int64_t m_value;
    };

    const Nanoseconds USEC(1000);
    const Nanoseconds MSEC(1000000);
    const Nanoseconds SEC(1000000000);

} // namespace

#endif // __UNITS_NANOSECONDS_H__
