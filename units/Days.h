#ifndef __UNITS_DAYS_H__
#define __UNITS_DAYS_H__

namespace units
{

    /**
     * Forward declataration of class.
     */
    class J2010_time;
    class GPS_time;
    class Seconds;

    class Days
    {
        public:

            /**
             * Constructor.
             * @param v Number of days.
             */
            explicit Days(double v = 0.0)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             */
            explicit Days(const Seconds& n);


            /**
             * Constructor.
             */
            explicit Days(const GPS_time& n);


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }


            /**
             * Type conversion from days to seconds.
             * @return days value conversion to seconds.
             */
            Seconds toSeconds() const;


            /**
             * Overload operator+
             * @param rhs Right hand side of the operation.
             * @return The added value
             */
            Days operator+(const Days& rhs) const
            {
                return Days(m_value + rhs.m_value);
            }


            /**
             * Overload operator-
             * @param rhs Right hand side of the operation.
             * @return The subtracted value.
             */
            Days operator-(const Days& rhs) const
            {
                return Days(m_value - rhs.m_value);
            }


            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            Days& operator+=(const Days& rhs)
            {
                m_value += rhs.m_value;

                return *this;
            }


            /**
             * Overload operator-=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value subtracted.
             */
            Days& operator-=(const Days& rhs)
            {
                m_value -= rhs.m_value;

                return *this;
            }


            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            Days& operator+=(const Seconds& rhs)
            {
                m_value += Days(rhs);

                return *this;
            }


            /**
             * Overload operator-=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value subtracted.
             */
            Days& operator-=(const Seconds& rhs)
            {
                m_value -= Days(rhs);

                return *this;
            }

        private:

            /**
             * Stored number of days.
             */
            double m_value;
    };

    const Days DAYS_PER_WEEK = Days(7.);

} // namespace

#endif // __UNITS_DAYS_H__
