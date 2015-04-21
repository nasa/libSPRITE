#ifndef __UNITS_GRAMS_H__
#define __UNITS_GRAMS_H__

namespace units
{

    class Grams
    {
      public:
        /**
         * Constructor.
         * @param v Number of Grams.
         */
        explicit Grams(double v)
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

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_GRAMS_H__
