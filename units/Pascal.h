
#ifndef __UNITS_PASCAL_H__
#define __UNITS_PASCAL_H__

#include "base/types.h"

namespace units {

    class Pascal {
      public:
        /**
         * Constructor.
         * @param v Number of seconds.
         * @satisfies{units-12.1}
         * @satisfies{units-12.2}
         * @satisfies{units-12.4}
         */
        explicit Pascal(int32_t v = 0.0) : m_value(v)
        {
        }

        /**
         * Type conversion to an integer.
         * @satisfies{units-12.3}
         */
        operator int32_t() const
        {
            return m_value;
        }

        /**
         * Overload operator+
         * @param rhs Right hand side of the operation.
         * @return The added value
         * @satisfies{units-12.5}
         */
        Pascal operator+(const Pascal &rhs) const
        {
            return Pascal(m_value + rhs.m_value);
        }

        /**
         * Overload operator-
         * @param rhs Right hand side of the operation.
         * @return The subtracted value.
         * @satisfies{units-12.5}
         */
        Pascal operator-(const Pascal &rhs) const
        {
            return Pascal(m_value - rhs.m_value);
        }

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
         * @satisfies{units-12.5}
         */
        Pascal &operator+=(const Pascal &rhs)
        {
            m_value += rhs.m_value;

            return *this;
        }

        /**
         * Overload operator-=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value subtracted.
         * @satisfies{units-12.5}
         */
        Pascal &operator-=(const Pascal &rhs)
        {
            m_value -= rhs.m_value;

            return *this;
        }

      private:
        /**
         * Stored number of seconds.
         */
        int32_t m_value;
    };

} // namespace

#endif // __UNITS_PASCAL_H__
