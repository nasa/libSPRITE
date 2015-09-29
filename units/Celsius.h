#ifndef __UNITS_CELSIUS_H__
#define __UNITS_CELSIUS_H__

namespace units {

    class Celsius {
      public:
        /**
         * Constructor.
         * @param v Number of seconds.
         * @satisfies{units-1.1}
         * @satisfies{units-1.2}
         * @satisfies{units-1.4}
         */
        explicit Celsius(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Type conversion to double.
         * @satisfies{units-1.3}
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
         * @satisfies{units-1.5}
         */
        Celsius &operator+=(const Celsius &rhs)
        {
            m_value += rhs.m_value;

            return *this;
        }

        /**
         * Overload operator-=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value subtracted.
         * @satisfies{units-1.5}
         */
        Celsius &operator-=(const Celsius &rhs)
        {
            m_value -= rhs.m_value;

            return *this;
        }

      private:
        /**
         * Stored number of seconds.
         */
        double m_value;
    };

} // namespace

#endif // __UNITS_CELSIUS_H__
