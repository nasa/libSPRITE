#ifndef __COORD_ECEF_H__
#define __COORD_ECEF_H__

#include "math/Vec3.h"
#include "units/Meters.h"
#include "coord/ECI.h"


namespace coord
{

    template<typename T> class ECEF : public math::Vec3<T>
    {
        private:

            /**
             * Constructor.
             * @param c Initial state vector.
             */
            explicit ECEF(math::Vec3<T> c) :
                math::Vec3<T>(c)
            {
            }

    };


    template<> class ECEF<units::Meters> : public math::Vec3<units::Meters>
    {
        public:

            /**
             * Constructor.
             * @param r Initial state vector.
             */
            explicit ECEF(math::Vec3<units::Meters> r) :
                math::Vec3<units::Meters>(r)
            {
            }

            /**
             * Constructor.
             * @param x X position.
             * @param y Y position.
             * @param z Z position.
             */
            ECEF(units::Meters x, units::Meters y, units::Meters z) :
                math::Vec3<units::Meters>(x, y, z)
            {
            }


#if 0
            /**
             * Convert to ECEF coordinate system.
             * @return Value in ECEF coordinate system.
             */
            ECEF toECI() const
            {
            }
#endif

    };

} // namespace

#endif // __COORD_ECEF_H__
