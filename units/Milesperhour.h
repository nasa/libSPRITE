#ifndef __UNITS_MILESPERHOUR_H__
#define __UNITS_MILESPERHOUR_H__

#include "base/types.h"
#include "units/Feetpersecond.h"
#include "units/Kilometersperhour.h"
#include "units/Meterspersecond.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Kilometersperhour;
    class Meterspersecond;
    class Feetpersecond;

    class Milesperhour
    {
      public:
        /**
         * Constructor.
         * @param v Number of Milesperhour.
         */
        explicit Milesperhour(double v)
            : m_value(v)
        {
        }

        /**
         * Constructor.
         */
        explicit Milesperhour(const Kilometersperhour &n);
        explicit Milesperhour(const Meterspersecond &n);
        explicit Milesperhour(const Feetpersecond &n);

        /**
         * Type conversion to double.
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Type conversion from Milesperhour to Feetpersecond.
         */
        units::Feetpersecond toFeetpersecond() const;

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_MILESPERHOUR_H__
