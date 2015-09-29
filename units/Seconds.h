#ifndef __UNITS_SECONDS_H__
#define __UNITS_SECONDS_H__

namespace units {

    /**
     * Forward declaration of class.
     */
    class Nanoseconds;
    class Days;

    class Seconds {
      public:
        /**
         * Constructor.
         * @param v Number of seconds.
         * @satisfies{units-15.1}
         * @satisfies{units-15.2}
         * @satisfies{units-15.4}
         */
        explicit Seconds(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Constructor.
         * @satisfies{units-15.7}
         */
        explicit Seconds(const Nanoseconds &n);

        /**
         * Constructor.
         * @satisfies{units-15.9}
         */
        explicit Seconds(const Days &n);

        /**
         * Type conversion to double.
         * @satisfies{units-15.3}
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Type conversion from seconds to nanoseconds.
         * @return seconds value conversion to nanoseconds.
         * @satisfies{units-15.6}
         */
        units::Nanoseconds toNanoseconds() const;

        /**
         * Type conversion from seconds to days.
         * @return seconds value conversion to days.
         * @satisfies{units-15.8}
         */
        units::Days toDays() const;

        /**
         * Overload operator+
         * @param rhs Right hand side of the operation.
         * @return The added value
         * @satisfies{units-15.5}
         */
        Seconds operator+(const Seconds &rhs) const
        {
            return Seconds(m_value + rhs.m_value);
        }

        /**
         * Overload operator-
         * @param rhs Right hand side of the operation.
         * @return The subtracted value.
         * @satisfies{units-15.5}
         */
        Seconds operator-(const Seconds &rhs) const
        {
            return Seconds(m_value - rhs.m_value);
        }

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
         * @satisfies{units-15.5}
         */
        Seconds &operator+=(const Seconds &rhs)
        {
            m_value += rhs.m_value;

            return *this;
        }

        /**
         * Overload operator-=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value subtracted.
         * @satisfies{units-15.5}
         */
        Seconds &operator-=(const Seconds &rhs)
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

    const Seconds SECONDS_PER_DAY = Seconds(60.0 * 60.0 * 24);
    const Seconds SECONDS_PER_WEEK = Seconds(SECONDS_PER_DAY * 7);

} // namespace

#endif // __UNITS_SECONDS_H__
