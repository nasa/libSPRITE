#include "math/DCM.h"
#include "math/Euler.h"
#include "math/Quaternion.h"
#include "math/trig.h"
#include "base/types.h"

#ifndef QUAT_NORMALIZATION_EPSILON
#define QUAT_NORMALIZATION_EPSILON 1e-12
#endif

namespace math {

    Quaternion::Quaternion(double s, const Vec3<> &v)
        : m_w(s)
        , m_v(v)
    {
        normalize();
    }

/* I haven't found a good test case for this so for know I'm just going to
 * comment it out. It can be put back in (with tests) if needed.
 */
#if 0
    Quaternion::Quaternion(const Vec3& rotation_vector,
            const units::Radians rotation_angle)
    {
        double hsa = sin(units::Radians(rotation_angle * 0.5));

        m_w = cos(units::Radians(rotation_angle * 0.5));
        m_v = Vec3(rotation_vector.x * hsa,
                rotation_vector.y * hsa,
                rotation_vector.z * hsa);

        normalize();
    }
#endif

    Quaternion::Quaternion(const Euler &e)
        : m_w(e.toQuaternion().scalar())
        , m_v(e.toQuaternion().vector())
    {
    }

    Quaternion::Quaternion(const DCM &dcm)
        : m_w(dcm.toQuaternion().scalar())
        , m_v(dcm.toQuaternion().vector())
    {
    }

    Quaternion Quaternion::operator*(const Quaternion &rhs) const
    {
        double w = m_w * rhs.m_w - m_v(1) * m_v(1) - m_v(2) * rhs.m_v(2) -
                   (m_v(3) * rhs.m_v(3));

        double x = m_w * rhs.m_v(1) + m_v(1) * m_w + m_v(2) * rhs.m_v(3) -
                   m_v(3) * rhs.m_v(2);

        double y = m_w * rhs.m_v(2) - m_v(1) * m_v(3) + m_v(2) * rhs.m_w +
                   m_v(3) * rhs.m_v(1);

        double z = m_w * rhs.m_v(3) + m_v(1) * m_v(2) - m_v(2) * rhs.m_v(1) +
                   m_v(3) * rhs.m_w;

        return Quaternion(w, Vec3<>(x, y, z));
    }

    Quaternion &Quaternion::operator*=(const Quaternion &rhs)
    {
        return *this = *this * rhs;
    }

    Vec3<> Quaternion::operator*(const Vec3<> &v) const
    {
        return toDCM() * v;
    }

    Quaternion Quaternion::conjugate() const
    {
        return Quaternion(m_w, m_v * -1);
    }

    Quaternion Quaternion::inverse() const
    {
        /* Because we always keep the quaternion normalized, the inverse is the
         * conjugate.
         */
        return conjugate();
    }

    Euler Quaternion::toEuler() const
    {
        const double sqw = m_w * m_w;
        const double sqx = m_v(1) * m_v(1);
        const double sqy = m_v(2) * m_v(2);
        const double sqz = m_v(3) * m_v(3);

        const units::Radians roll = units::Radians(
            atan2(2 * (m_v(2) * m_v(3) + m_v(1) * m_w), sqw - sqx - sqy + sqz));

        const units::Radians pitch =
            units::Radians(asin2(-2 * (m_v(1) * m_v(3) - m_v(2) * m_w)));

        const units::Radians yaw = units::Radians(
            atan2(2 * (m_v(1) * m_v(2) + m_v(3) * m_w), sqw + sqx - sqy - sqz));

        return Euler(roll, pitch, yaw);
    }

    DCM Quaternion::toDCM() const
    {
        return DCM(1.0 - 2.0 * (m_v(2) * m_v(2) + m_v(3) * m_v(3)),
                   2.0 * (m_v(1) * m_v(2) + m_w * m_v(3)),
                   2.0 * (m_v(1) * m_v(3) - m_w * m_v(2)),
                   2.0 * (m_v(1) * m_v(2) - m_w * m_v(3)),
                   1.0 - 2.0 * (m_v(1) * m_v(1) + m_v(3) * m_v(3)),
                   2.0 * (m_v(2) * m_v(3) + m_w * m_v(1)),
                   2.0 * (m_v(1) * m_v(3) + m_w * m_v(2)),
                   2.0 * (m_v(2) * m_v(3) - m_w * m_v(1)),
                   1.0 - 2.0 * (m_v(1) * m_v(1) + m_v(2) * m_v(2)));
    }

    void Quaternion::normalize()
    {
        double mag2 =
            m_w * m_w + m_v(1) * m_v(1) + m_v(2) * m_v(2) + m_v(3) * m_v(3);

        /* Only normalize the quaternion if the magnitude diverges from 1 by
         * more than some epsilon to make more efficient.
         * We use the magnitude squared value because it should still be near 1
         * and the sqrt() function is expensive. If you've already done the
         * sqrt() then you might as well divide.
         */
        if(fabs(mag2 - 1) > QUAT_NORMALIZATION_EPSILON) {
            double mag = sqrt(mag2);

            m_w /= mag;
            m_v /= mag;

            if(fabs(m_w) <= NEAR_ZERO) {
                m_w = 0;
            }
        }
    }

} // namespace
