#ifndef __UNITS_GRAMS_H__
#define __UNITS_GRAMS_H__

namespace units {

    class Grams {
      public:
        /**
         * Constructor.
         * @param v Number of Grams.
         * @satisfies{units-5.1}
         * @satisfies{units-5.2}
         * @satisfies{units-5.4}
         */
        explicit Grams(double v = 0.0) : m_value(v)
        {
        }

        /**
         * Type conversion to double.
         * @satisfies{units-5.3}
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
