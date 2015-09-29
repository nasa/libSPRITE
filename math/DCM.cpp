#include "math/DCM.h"
#include "math/Euler.h"
#include "math/Quaternion.h"
#include "trig.h"

namespace math {

    DCM::DCM(const Euler &e)
    {
        *this = e.toDCM();
    }

    Euler DCM::toEuler() const
    {
        return Euler(atan2(m_[2][1], m_[2][2]),
                     units::Radians(-asin2(m_[2][0])),
                     atan2(m_[1][0], m_[0][0]));
    }

    Quaternion DCM::toQuaternion() const
    {
        double w, x, y, z;
        const double s0 = 1 + m_[0][0] + m_[1][1] + m_[2][2];
        const double sx = 1 + m_[0][0] - m_[1][1] - m_[2][2];
        const double sy = 1 - m_[0][0] + m_[1][1] - m_[2][2];
        const double sz = 1 - m_[0][0] - m_[1][1] + m_[2][2];

        if((s0 >= sx) && (s0 >= sy) && (s0 >= sz)) {
            w = sqrt(0.25 * s0);
            const double w4 = w * 4;
            x = (m_[1][2] - m_[2][1]) / w4;
            y = (m_[2][0] - m_[0][2]) / w4;
            z = (m_[0][1] - m_[1][0]) / w4;
        } else if((sx >= sy) && (sx >= sz)) {
            x = sqrt(0.25 * sx);
            const double x4 = x * 4;
            w = (m_[1][2] - m_[2][1]) / x4;
            y = (m_[0][1] + m_[1][0]) / x4;
            z = (m_[2][0] + m_[0][2]) / x4;
        } else if(sy >= sz) {
            y = sqrt(0.25 * sy);
            const double y4 = y * 4;
            w = (m_[2][0] - m_[0][2]) / y4;
            x = (m_[0][1] + m_[1][0]) / y4;
            z = (m_[1][2] + m_[2][1]) / y4;
        } else {
            z = sqrt(0.25 * sz);
            const double z4 = z * 4;
            w = (m_[0][1] - m_[1][0]) / z4;
            x = (m_[2][0] + m_[0][2]) / z4;
            y = (m_[1][2] + m_[2][1]) / z4;
        }

        return Quaternion(w, Vec3<>(x, y, z));
    }

} // namespace
