#include <math.h>
#include "math/Vec3_ut.h"
#include "math/Vec3.h"
#include "units/Meters.h"

namespace math {

    void Vec3_ut::setUp()
    {
    }

    void Vec3_ut::tearDown()
    {
    }

    void Vec3_ut::test_Vec3()
    {
        Vec3<> v;

        CPPUNIT_ASSERT_THROW(v(0), int);
        CPPUNIT_ASSERT_THROW(v(4), int);

        CPPUNIT_ASSERT_EQUAL(0.0, v(1));
        CPPUNIT_ASSERT_EQUAL(0.0, v(2));
        CPPUNIT_ASSERT_EQUAL(0.0, v(3));
    }

    void Vec3_ut::test_Vec3_init()
    {
        Vec3<> v(1, 2, 3);

        CPPUNIT_ASSERT_EQUAL(1.0, v(1));
        CPPUNIT_ASSERT_EQUAL(2.0, v(2));
        CPPUNIT_ASSERT_EQUAL(3.0, v(3));
    }

    void Vec3_ut::test_add_scalar()
    {
        const double s = 1.23;
        const Vec3<> v(1, 2, 3);
        const Vec3<> v1 = v + s;

        CPPUNIT_ASSERT_EQUAL(s + 1, v1(1));
        CPPUNIT_ASSERT_EQUAL(s + 2, v1(2));
        CPPUNIT_ASSERT_EQUAL(s + 3, v1(3));
    }

    void Vec3_ut::test_subtract_scalar()
    {
        const double s = 1.23;
        const Vec3<> v(1, 2, 3);
        const Vec3<> v1 = v - s;

        CPPUNIT_ASSERT_EQUAL(1 - s, v1(1));
        CPPUNIT_ASSERT_EQUAL(2 - s, v1(2));
        CPPUNIT_ASSERT_EQUAL(3 - s, v1(3));
    }

    void Vec3_ut::test_multiply_scalar()
    {
        const double s = 1.23;
        const Vec3<> v(1, 2, 3);
        const Vec3<> v1 = v * s;

        CPPUNIT_ASSERT_EQUAL(1 * s, v1(1));
        CPPUNIT_ASSERT_EQUAL(2 * s, v1(2));
        CPPUNIT_ASSERT_EQUAL(3 * s, v1(3));
    }

    void Vec3_ut::test_divide_scalar()
    {
        const double s = 1.23;
        const Vec3<> v(1, 2, 3);
        const Vec3<> v1 = v / s;

        /* Divide by zero should cause an assertion.
         */
        CPPUNIT_ASSERT_THROW(v / 0, int);

        CPPUNIT_ASSERT_EQUAL(1 / s, v1(1));
        CPPUNIT_ASSERT_EQUAL(2 / s, v1(2));
        CPPUNIT_ASSERT_EQUAL(3 / s, v1(3));
    }

    void Vec3_ut::test_add_equal_scalar()
    {
        const double s = 1.23;
        Vec3<> v(1, 2, 3);

        v += s;

        CPPUNIT_ASSERT_EQUAL(1 + s, v(1));
        CPPUNIT_ASSERT_EQUAL(2 + s, v(2));
        CPPUNIT_ASSERT_EQUAL(3 + s, v(3));
    }

    void Vec3_ut::test_subtract_equal_scalar()
    {
        const double s = 1.23;
        Vec3<> v(1, 2, 3);

        v -= s;

        CPPUNIT_ASSERT_EQUAL(1 - s, v(1));
        CPPUNIT_ASSERT_EQUAL(2 - s, v(2));
        CPPUNIT_ASSERT_EQUAL(3 - s, v(3));
    }

    void Vec3_ut::test_multiply_equal_scalar()
    {
        const double s = 1.23;
        Vec3<> v(1, 2, 3);

        v *= s;

        CPPUNIT_ASSERT_EQUAL(1 * s, v(1));
        CPPUNIT_ASSERT_EQUAL(2 * s, v(2));
        CPPUNIT_ASSERT_EQUAL(3 * s, v(3));
    }

    void Vec3_ut::test_divide_equal_scalar()
    {
        const double s = 1.23;
        Vec3<> v(1, 2, 3);

        v /= s;

        CPPUNIT_ASSERT_EQUAL(1 / s, v(1));
        CPPUNIT_ASSERT_EQUAL(2 / s, v(2));
        CPPUNIT_ASSERT_EQUAL(3 / s, v(3));

        /* Divide by zero should cause an assertion.
         */
        CPPUNIT_ASSERT_THROW(v /= 0, int);
    }

    void Vec3_ut::test_add_vector()
    {
        const Vec3<> a(1, 2, 3);
        const Vec3<> b(4, 5, 6);
        const Vec3<> v = a + b;

        CPPUNIT_ASSERT_EQUAL(1.0 + 4.0, v(1));
        CPPUNIT_ASSERT_EQUAL(2.0 + 5.0, v(2));
        CPPUNIT_ASSERT_EQUAL(3.0 + 6.0, v(3));
    }

    void Vec3_ut::test_subtract_vector()
    {
        const Vec3<> a(1, 2, 3);
        const Vec3<> b(4, 5, 6);
        const Vec3<> v = a - b;

        CPPUNIT_ASSERT_EQUAL(1.0 - 4.0, v(1));
        CPPUNIT_ASSERT_EQUAL(2.0 - 5.0, v(2));
        CPPUNIT_ASSERT_EQUAL(3.0 - 6.0, v(3));
    }

    void Vec3_ut::test_add_equal_vector()
    {
        Vec3<> a(1, 2, 3);
        const Vec3<> b(4, 5, 6);

        a += b;

        CPPUNIT_ASSERT_EQUAL(1.0 + 4.0, a(1));
        CPPUNIT_ASSERT_EQUAL(2.0 + 5.0, a(2));
        CPPUNIT_ASSERT_EQUAL(3.0 + 6.0, a(3));
    }

    void Vec3_ut::test_subtract_equal_vector()
    {
        Vec3<> a(1, 2, 3);
        const Vec3<> b(4, 5, 6);

        a -= b;

        CPPUNIT_ASSERT_EQUAL(1.0 - 4.0, a(1));
        CPPUNIT_ASSERT_EQUAL(2.0 - 5.0, a(2));
        CPPUNIT_ASSERT_EQUAL(3.0 - 6.0, a(3));
    }

    void Vec3_ut::test_magnitude_squared()
    {
        const Vec3<> a(1, 2, 3);

        CPPUNIT_ASSERT(1 * 1 + 2 * 2 + 3 * 3 == a.magnitude_squared());
    }

    void Vec3_ut::test_magnitude()
    {
        const Vec3<> a(1, 2, 3);

        CPPUNIT_ASSERT(sqrt(1 * 1 + 2 * 2 + 3 * 3) == a.magnitude());
    }

    void Vec3_ut::test_normalize()
    {
        Vec3<> a(1, 2, 3);

        a.normalize();

        CPPUNIT_ASSERT(1 == a.magnitude());
    }

    void Vec3_ut::test_dot()
    {
        const Vec3<> a(1, 2, 3);
        const Vec3<> b(4, 5, 6);

        CPPUNIT_ASSERT(1 * 4 + 2 * 5 + 3 * 6 == a.dot(b));
    }

    void Vec3_ut::test_cross()
    {
        const Vec3<> a(1, 2, 3);
        const Vec3<> b(4, 5, 6);
        const Vec3<> v = cross(a, b);

        CPPUNIT_ASSERT((2 * 6 - 3 * 5 == v(1)) && (3 * 4 - 1 * 6 == v(2)) &&
                       (1 * 5 - 2 * 4 == v(3)));
    }

    void Vec3_ut::test_cross_cast()
    {
        const Vec3<units::Meters> a(units::Meters(1.0), units::Meters(2.0),
                                    units::Meters(3.0));
        const Vec3<> b(4, 5, 6);
        const Vec3<> v = cross(Vec3<>(a(1), a(2), a(3)), b);

        CPPUNIT_ASSERT((2 * 6 - 3 * 5 == v(1)) && (3 * 4 - 1 * 6 == v(2)) &&
                       (1 * 5 - 2 * 4 == v(3)));
    }

} // namespace
