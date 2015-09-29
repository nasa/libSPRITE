#ifndef __UNITS_MILLIMETERS_H__
#define __UNITS_MILLIMETERS_H__

#include <math.h>
#include "base/types.h"

namespace units {

    /**
     * Forward declaration of class.
     */
    class Meters;

    class Millimeters {
      public:
        /**
         * Constructor.
         * @param v Number of seconds.
         * @satisfies{units-17.1}
         * @satisfies{units-17.2}
         * @satisfies{units-17.4}
         */
        explicit Millimeters(int64_t v = 0) : m_value(v)
        {
        }

        /**
         * Constructor.
         * @satisfies{units-17.11}
         */
        explicit Millimeters(const Meters &m);

        /**
         * Type conversion to 64-bit integer.
         * @satisfies{units-17.3}
         */
        operator int64_t() const
        {
            return m_value;
        }

        /**
         * Type conversion from Millimeters to Meters.
         * @satisfies{units-17.10}
         */
        units::Meters toMeters() const;

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
         * @satisfies{units-17.5}
         */
        Millimeters &operator+=(const Millimeters &rhs)
        {
            m_value += rhs.m_value;

            return *this;
        }

        /**
         * Overload operator-=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value subtracted.
         * @satisfies{units-17.5}
         */
        Millimeters &operator-=(const Millimeters &rhs)
        {
            m_value -= rhs.m_value;

            return *this;
        }

        /**
         * Overload operator*=
         * @param rhs Right hand side of the operation.
         * @return This instance divided by the right hand side.
         * @satisfies{units-17.5}
         */
        Millimeters &operator*=(const Millimeters &rhs)
        {
            m_value *= rhs.m_value;

            return *this;
        }

        /**
         * Overload operator/=
         * @param rhs Right hand side of the operation.
         * @return This instance divided by the right hand side.
         * @satisfies{units-17.5}
         */
        Millimeters &operator/=(const Millimeters &rhs)
        {
            m_value /= rhs.m_value;

            return *this;
        }

      private:
        /**
         * Stored value.
         */
        int64_t m_value;
    };

} // namespace

#endif // __UNITS_MILLIMETERS_H__
