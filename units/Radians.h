#ifndef __UNITS_RADIANS_H__
#define __UNITS_RADIANS_H__

namespace units {

    /**
     * Forward declaration of class.
     */
    class Degrees;

    class Radians {
      public:
        /**
         * Default constructor
         * @satisfies{units-13.1}
         * @satisfies{units-13.2}
         * @satisfies{units-13.4}
         */
        explicit Radians(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Constructor.
         * @param d Units of degrees to be converted to radians.
         * @satisfies{units-13.7}
         */
        explicit Radians(const Degrees &d);

        /**
         * Type conversion to double.
         * @satisfies{units-13.3}
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Type conversion from radians to degrees.
         * @return Radian value converted to degrees.
         * @satisfies{units-13.6}
         */
        Degrees toDegrees() const;

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_RADIANS_H__
