#ifndef __UNITS_DEGREES_H__
#define __UNITS_DEGREES_H__

namespace units
{

    /**
     * Forward declaration of class.
     */
    class Radians;

    class Degrees
    {
        public:

            /**
             * Constructor.
             * @param v Floating point value of radians.
             */
            explicit Degrees(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             * @param r Units of radians to be converted to degrees.
             */
            explicit Degrees(const Radians& r);


            /**
             * Type conversion to double.
             */
            operator double() const
            {
                return m_value;
            }

            /**
             * Type conversion from radians to degrees.
             * @return Radian value converted to degrees.
             */
            Radians toRadians() const;

        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_DEGREES_H__
