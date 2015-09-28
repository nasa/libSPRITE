#include "math/DCM.h"
#include "math/Euler.h"
#include "math/Quaternion.h"
#include "math/trig.h"

namespace math {

    Euler::Euler(const Quaternion q)
        : m_roll(q.toEuler().get_roll())
        , m_pitch(q.toEuler().get_pitch())
        , m_yaw(q.toEuler().get_yaw())
    {
    }

    DCM Euler::toDCM() const
    {
        const double sr = sin(m_roll);
        const double sp = sin(m_pitch);
        const double sy = sin(m_yaw);
        const double cr = cos(m_roll);
        const double cp = cos(m_pitch);
        const double cy = cos(m_yaw);

        const double spsy = sp * sy;
        const double spcy = sp * cy;

        return DCM(cp * cy, cp * sy, -sp, sr * spcy - cr * sy,
                   sr * spsy + cr * cy, sr * cp, cr * spcy + sr * sy,
                   cr * spsy - sr * cy, cr * cp);
    }

    Quaternion Euler::toQuaternion() const
    {
        units::Radians angle = units::Radians(m_roll * 0.5);
        const double sr = sin(angle);
        const double cr = cos(angle);

        angle = units::Radians(m_pitch * 0.5);
        const double sp = sin(angle);
        const double cp = cos(angle);

        angle = units::Radians(m_yaw * 0.5);
        const double sy = sin(angle);
        const double cy = cos(angle);

        const double cpcy = cp * cy;
        const double spcy = sp * cy;
        const double cpsy = cp * sy;
        const double spsy = sp * sy;

        return Quaternion(cr * cpcy + sr * spsy,
                          Vec3<>(sr * cpcy - cr * spsy, cr * spcy + sr * cpsy,
                                 cr * cpsy - sr * spcy));
    }

} // namespace
