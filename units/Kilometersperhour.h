#ifndef __UNITS_KILOMETERSPERHOUR_H__
#define __UNITS_KILOMETERSPERHOUR_H__

#include "base/types.h"
#include "units/Feetpersecond.h"
#include "units/Milesperhour.h"
#include "units/Meterspersecond.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Meterspersecond;
    class Feetpersecond;
    class Milesperhour;

    class Kilometersperhour
    {
      public:
        /**
         * Constructor.
         * @param v Number of Kilometersperhour.
         */
        explicit Kilometersperhour(double v)
            : m_value(v)
        {
        }

        /**
         * Constructor.
         */
        explicit Kilometersperhour(const Meterspersecond &n);
        explicit Kilometersperhour(const Feetpersecond &n);
        explicit Kilometersperhour(const Milesperhour &n);

        /**
         * Type conversion to double.
         */
        operator double() const
        {
            return m_value;
        }

        /**
         * Type conversion from Kilometersperhour to Meterspersecond.
         */
        units::Meterspersecond toMeterspersecond() const;

      private:
        double m_value;
    };

} // namespace

#endif // __UNITS_KILOMETERSPERHOUR_H__
