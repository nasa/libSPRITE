#include "math/Vec3.h"

namespace math {

    Vec3<> cross(const Vec3<> &v1, const Vec3<> &v2)
    {
        return Vec3<>(v1(2) * v2(3) - v1(3) * v2(2),
                      v1(3) * v2(1) - v1(1) * v2(3),
                      v1(1) * v2(2) - v1(2) * v2(1));
    }
}
