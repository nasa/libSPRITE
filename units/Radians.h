#ifndef __UNITS_RADIANS_H__
#define __UNITS_RADIANS_H__


namespace units
{

    /**
     * Forward declaration of class.
     */
    class Degrees;

    class Radians
    {
        public:

            /**
             * Default constructor
             */
            Radians()
                : m_value(0)
            {
            }

            /**
             * Constructor.
             * @param v Floating point value of radians.
             */
            explicit Radians(double v)
                : m_value(v)
            {
            }


            /**
             * Constructor.
             * @param d Units of degrees to be converted to radians.
             */
            explicit Radians(const Degrees& d);


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
            Degrees toDegrees() const;

        private:
            double m_value;
    };

} // namespace

#endif // __UNITS_RADIANS_H__
