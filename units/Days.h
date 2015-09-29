#ifndef __UNITS_DAYS_H__
#define __UNITS_DAYS_H__

namespace units {

    /**
     * Forward declataration of class.
     */
    class GPS_time;
    class Seconds;

    class Days {
      public:
        /**
         * Constructor.
         * @param v Number of days.
         * @satisfies{units-2.1}
         * @satisfies{units-2.2}
         * @satisfies{units-2.4}
         */
        explicit Days(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Constructor.
         * @satisfies{units-2.8}
         */
        explicit Days(const Seconds &n);

        /**
         * Type conversion to double.
         * @satisfies{units-2.3}
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Type conversion from days to seconds.
         * @return days value conversion to seconds.
         * @satisfies{units-2.10}
         */
        Seconds toSeconds() const;

        /**
         * Overload operator+=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value added.
         * @satisfies{units-2.5}
         */
        Days &operator+=(const Days &rhs)
        {
            m_value += rhs.m_value;

            return *this;
        }

        /**
         * Overload operator-=
         * @param rhs Right hand side of the operation.
         * @return This instance with the right hand side value subtracted.
         * @satisfies{units-2.5}
         */
        Days &operator-=(const Days &rhs)
        {
            m_value -= rhs.m_value;

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
