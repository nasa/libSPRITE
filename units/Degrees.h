#ifndef __UNITS_DEGREES_H__
#define __UNITS_DEGREES_H__

namespace units {

    /**
     * Forward declaration of class.
     */
    class Radians;

    class Degrees {
      public:
        /**
         * Constructor.
         * @param v Floating point value of radians.
         * @satisfies{units-3.1}
         * @satisfies{units-3.2}
         * @satisfies{units-3.4}
         */
        explicit Degrees(double v = 0) : m_value(v)
        {
        }

        /**
         * Constructor.
         * @param r Units of radians to be converted to degrees.
         * @satisfies{units-3.6}
         */
        explicit Degrees(const Radians &r);

        /**
         * Type conversion to double.
         * @satisfies{units-3.3}
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Type conversion from radians to degrees.
         * @return Radian value converted to degrees.
         * @satisfies{units-3.7}
         */
        Radians toRadians() const;

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_DEGREES_H__
