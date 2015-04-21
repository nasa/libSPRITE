
#ifndef __UNITS_PASCAL_H__
#define __UNITS_PASCAL_H__

#include "base/types.h"

namespace units
{

    class Pascal
    {
      public:
        /**
         * Constructor.
         * @param v Number of seconds.
         */
        explicit Pascal(uint32_t v = 0.0)
            : m_value(v)
        {
        }

        /**
         * Type conversion to an integer.
         */
        operator uint32_t() const
        {
            return m_value;
        }

        /**
         * Overload operator+
         * @param rhs Right hand side of the operation.
         * @return The added value
         */
        Pascal operator+(const Pascal &rhs) const
        {
            return Pascal(m_value + rhs.m_value);
        }

        /**
         * Overload operator-
         * @param rhs Right hand side of the operation.
         * @return The subtracted value.
         */
        Pascal operator-(const Pascal &rhs) const
        {
            return Pascal(m_value - rhs.m_value);
        }

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
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
        uint32_t m_value;
    };

} // namespace

#endif // __UNITS_PASCAL_H__
