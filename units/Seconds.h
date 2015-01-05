#ifndef __UNITS_SECONDS_H__
#define __UNITS_SECONDS_H__

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Nanoseconds;
    class Days;

    class Seconds
    {
        public:

            /**
             * Constructor.
             * @param v Number of seconds.
             */
            explicit Seconds(double v = 0.0)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Seconds(const Nanoseconds& n);


            /**
             * Constructor.
             */
            explicit Seconds(const Days& n);


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Type conversion from seconds to nanoseconds.
             * @return seconds value conversion to nanoseconds.
             */
            units::Nanoseconds toNanoseconds() const;


            /**
             * Type conversion from seconds to days.
             * @return seconds value conversion to days.
             */
            units::Days toDays() const;


            /**
             * Overload operator+
             * @param rhs Right hand side of the operation.
             * @return The added value
             */
            Seconds operator+(const Seconds& rhs) const
            {
                return Seconds(m_value + rhs.m_value);
            }


            /**
             * Overload operator-
             * @param rhs Right hand side of the operation.
             * @return The subtracted value.
             */
            Seconds operator-(const Seconds& rhs) const
            {
                return Seconds(m_value - rhs.m_value);
            }


            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            Seconds& operator+=(const Seconds& rhs)
            {
                m_value += rhs.m_value;

                return *this;
            }


            /**
             * Overload operator-=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value subtracted.
             */
            Seconds& operator-=(const Seconds& rhs)
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
