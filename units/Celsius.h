#ifndef __UNITS_CELSIUS_H__
#define __UNITS_CELSIUS_H__

namespace units
{

    class Celsius
    {
        public:

            /**
             * Constructor.
             * @param v Number of seconds.
             */
            explicit Celsius(double v = 0.0)
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
            Celsius operator+(const Celsius& rhs) const
            {
                return Celsius(m_value + rhs.m_value);
            }


            /**
             * Overload operator-
             * @param rhs Right hand side of the operation.
             * @return The subtracted value.
             */
            Celsius operator-(const Celsius& rhs) const
            {
                return Celsius(m_value - rhs.m_value);
            }


            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            Celsius& operator+=(const Celsius& rhs)
            {
                m_value += rhs.m_value;

                return *this;
            }


            /**
             * Overload operator-=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value subtracted.
             */
            Celsius& operator-=(const Celsius& rhs)
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
