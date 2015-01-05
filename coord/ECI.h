#ifndef __COORD_ECI_H__
#define __COORD_ECI_H__

#include "coord/ECEF.h"
#include "math/DCM.h"
#include "math/trig.h"
#include "math/Vec3.h"
#include "units/Meters.h"
#include "units/Radians.h"


namespace coord
{

    template<typename T> class ECI : public math::Vec3<T>
    {
        private:

            /**
             * Constructor.
             * @param c Initial state vector.
             */
            explicit ECI(math::Vec3<T> c) :
                math::Vec3<T>(c)
            {
            }

    };

    template<> class ECI<units::Meters> : public math::Vec3<units::Meters>
    {
        public:

            /**
             * Constructor.
             * @param r Initial state vector.
             */
            explicit ECI(math::Vec3<units::Meters> r) :
                math::Vec3<units::Meters>(r)
            {
            }

            /**
             * Constructor.
             * @param x X position.
             * @param y Y position.
             * @param z Z position.
             */
            ECI(units::Meters x, units::Meters y, units::Meters z) :
                math::Vec3<units::Meters>(x, y, z)
            {
            }


            /**
             * Convert to ECEF coordinate system.
             * @param theta Greenwich Sidreal Angle.
             * @return Value in ECEF coordinate system.
             */
            ECEF<units::Meters> toECEF(const units::Radians& theta) const
            {
                double sth = math::sin(theta);
                double cth = math::cos(theta);
                math::DCM T(cth, sth, 0, -sth, cth, 0, 0, 0, 1);

                math::Vec3<> res = T * math::Vec3<>(m_[0], m_[1], m_[2]);
                return ECEF<units::Meters>(units::Meters(res(1)),
                        units::Meters(res(2)), units::Meters(res(3)));
            }

    };

} // namespace

#endif // __COORD_ECI_H__
