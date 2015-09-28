#include <math.h>
#include "math/Matrix3.h"
#include "math/Matrix3_ut.h"
#include "math/Vec3.h"
#include "base/XPRINTF.h"

namespace math {

    void Matrix3_ut::setUp()
    {
    }

    void Matrix3_ut::tearDown()
    {
    }

    void Matrix3_ut::test_Matrix3()
    {
        Matrix3 m;

        CPPUNIT_ASSERT((0 == m(1, 1)) && (0 == m(1, 2)) && (0 == m(1, 3)) &&
                       (0 == m(2, 1)) && (0 == m(2, 2)) && (0 == m(2, 3)) &&
                       (0 == m(3, 1)) && (0 == m(3, 2)) && (0 == m(3, 3)));
    }

    void Matrix3_ut::test_Matrix3_init()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        CPPUNIT_ASSERT((1 == m(1, 1)) && (2 == m(1, 2)) && (3 == m(1, 3)) &&
                       (4 == m(2, 1)) && (5 == m(2, 2)) && (6 == m(2, 3)) &&
                       (7 == m(3, 1)) && (8 == m(3, 2)) && (9 == m(3, 3)));
    }

    void Matrix3_ut::test_equal()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(1, 2, 3, 4, 5, 6, 7, 8, 9);

        CPPUNIT_ASSERT(m == n);

        n(3, 3) = 0;

        CPPUNIT_ASSERT(false == (m == n));
    }

    void Matrix3_ut::test_not_equal()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(1, 2, 3, 4, 5, 6, 7, 8, 9);

        CPPUNIT_ASSERT(false == (m != n));

        n(3, 3) = 0;

        CPPUNIT_ASSERT(m != n);
    }

    void Matrix3_ut::test_get_set()
    {
        Matrix3 m;

        /* Test that out-of-bounds accesses cause an assert/exception).
         */
        CPPUNIT_ASSERT_THROW(m(0, 1), int);
        CPPUNIT_ASSERT_THROW(m(1, 0), int);
        CPPUNIT_ASSERT_THROW(m(4, 1), int);
        CPPUNIT_ASSERT_THROW(m(1, 4), int);

        CPPUNIT_ASSERT((0 == m(1, 1)) && (0 == m(1, 2)) && (0 == m(1, 3)) &&
                       (0 == m(2, 1)) && (0 == m(2, 2)) && (0 == m(2, 3)) &&
                       (0 == m(3, 1)) && (0 == m(3, 2)) && (0 == m(3, 3)));

        m(2, 2) = 3.14;

        CPPUNIT_ASSERT((0 == m(1, 1)) && (0 == m(1, 2)) && (0 == m(1, 3)) &&
                       (0 == m(2, 1)) && (3.14 == m(2, 2)) && (0 == m(2, 3)) &&
                       (0 == m(3, 1)) && (0 == m(3, 2)) && (0 == m(3, 3)));

        m(2, 2) = 0;
        m(1, 1) = 3.14;

        CPPUNIT_ASSERT((3.14 == m(1, 1)) && (0 == m(1, 2)) && (0 == m(1, 3)) &&
                       (0 == m(2, 1)) && (0 == m(2, 2)) && (0 == m(2, 3)) &&
                       (0 == m(3, 1)) && (0 == m(3, 2)) && (0 == m(3, 3)));

        m(1, 1) = 0;
        m(3, 3) = 3.14;

        CPPUNIT_ASSERT((0 == m(1, 1)) && (0 == m(1, 2)) && (0 == m(1, 3)) &&
                       (0 == m(2, 1)) && (0 == m(2, 2)) && (0 == m(2, 3)) &&
                       (0 == m(3, 1)) && (0 == m(3, 2)) && (3.14 == m(3, 3)));
    }

    void Matrix3_ut::test_add_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 r = m + 1;

        CPPUNIT_ASSERT((2 == r(1, 1)) && (3 == r(1, 2)) && (4 == r(1, 3)) &&
                       (5 == r(2, 1)) && (6 == r(2, 2)) && (7 == r(2, 3)) &&
                       (8 == r(3, 1)) && (9 == r(3, 2)) && (10 == r(3, 3)));
        CPPUNIT_ASSERT((1 == m(1, 1)) && (2 == m(1, 2)) && (3 == m(1, 3)) &&
                       (4 == m(2, 1)) && (5 == m(2, 2)) && (6 == m(2, 3)) &&
                       (7 == m(3, 1)) && (8 == m(3, 2)) && (9 == m(3, 3)));
    }

    void Matrix3_ut::test_subtract_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 r = m - 4;

        CPPUNIT_ASSERT((-3 == r(1, 1)) && (-2 == r(1, 2)) && (-1 == r(1, 3)) &&
                       (0 == r(2, 1)) && (1 == r(2, 2)) && (2 == r(2, 3)) &&
                       (3 == r(3, 1)) && (4 == r(3, 2)) && (5 == r(3, 3)));
        CPPUNIT_ASSERT((1 == m(1, 1)) && (2 == m(1, 2)) && (3 == m(1, 3)) &&
                       (4 == m(2, 1)) && (5 == m(2, 2)) && (6 == m(2, 3)) &&
                       (7 == m(3, 1)) && (8 == m(3, 2)) && (9 == m(3, 3)));
    }

    void Matrix3_ut::test_multiply_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 r = m * 2;

        CPPUNIT_ASSERT((2 == r(1, 1)) && (4 == r(1, 2)) && (6 == r(1, 3)) &&
                       (8 == r(2, 1)) && (10 == r(2, 2)) && (12 == r(2, 3)) &&
                       (14 == r(3, 1)) && (16 == r(3, 2)) && (18 == r(3, 3)));
        CPPUNIT_ASSERT((1 == m(1, 1)) && (2 == m(1, 2)) && (3 == m(1, 3)) &&
                       (4 == m(2, 1)) && (5 == m(2, 2)) && (6 == m(2, 3)) &&
                       (7 == m(3, 1)) && (8 == m(3, 2)) && (9 == m(3, 3)));
    }

    void Matrix3_ut::test_divide_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 r = m / 2;

        CPPUNIT_ASSERT((0.5 == r(1, 1)) && (1 == r(1, 2)) && (1.5 == r(1, 3)) &&
                       (2 == r(2, 1)) && (2.5 == r(2, 2)) && (3 == r(2, 3)) &&
                       (3.5 == r(3, 1)) && (4 == r(3, 2)) && (4.5 == r(3, 3)));
        CPPUNIT_ASSERT((1 == m(1, 1)) && (2 == m(1, 2)) && (3 == m(1, 3)) &&
                       (4 == m(2, 1)) && (5 == m(2, 2)) && (6 == m(2, 3)) &&
                       (7 == m(3, 1)) && (8 == m(3, 2)) && (9 == m(3, 3)));

        /* Divide by zero should cause an assertion.
         */
        CPPUNIT_ASSERT_THROW(m / 0, int);
    }

    void Matrix3_ut::test_add_equal_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        m += 1;

        CPPUNIT_ASSERT((2 == m(1, 1)) && (3 == m(1, 2)) && (4 == m(1, 3)) &&
                       (5 == m(2, 1)) && (6 == m(2, 2)) && (7 == m(2, 3)) &&
                       (8 == m(3, 1)) && (9 == m(3, 2)) && (10 == m(3, 3)));
    }

    void Matrix3_ut::test_subtract_equal_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        m -= 4;

        CPPUNIT_ASSERT((-3 == m(1, 1)) && (-2 == m(1, 2)) && (-1 == m(1, 3)) &&
                       (0 == m(2, 1)) && (1 == m(2, 2)) && (2 == m(2, 3)) &&
                       (3 == m(3, 1)) && (4 == m(3, 2)) && (5 == m(3, 3)));
    }

    void Matrix3_ut::test_multiply_equal_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        m *= 2;

        CPPUNIT_ASSERT((2 == m(1, 1)) && (4 == m(1, 2)) && (6 == m(1, 3)) &&
                       (8 == m(2, 1)) && (10 == m(2, 2)) && (12 == m(2, 3)) &&
                       (14 == m(3, 1)) && (16 == m(3, 2)) && (18 == m(3, 3)));
    }

    void Matrix3_ut::test_divide_equal_scalar()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        m /= 2;

        CPPUNIT_ASSERT((0.5 == m(1, 1)) && (1 == m(1, 2)) && (1.5 == m(1, 3)) &&
                       (2 == m(2, 1)) && (2.5 == m(2, 2)) && (3 == m(2, 3)) &&
                       (3.5 == m(3, 1)) && (4 == m(3, 2)) && (4.5 == m(3, 3)));

        /* Divide by zero should cause an assertion.
         */
        CPPUNIT_ASSERT_THROW(m /= 0, int);
    }

    void Matrix3_ut::test_add_matrix()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(9, 8, 7, 6, 5, 4, 3, 2, 1);
        Matrix3 r = m + n;

        CPPUNIT_ASSERT((10 == r(1, 1)) && (10 == r(1, 2)) && (10 == r(1, 3)) &&
                       (10 == r(2, 1)) && (10 == r(2, 2)) && (10 == r(2, 3)) &&
                       (10 == r(3, 1)) && (10 == r(3, 2)) && (10 == r(3, 3)));
    }

    void Matrix3_ut::test_substract_matrix()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(9, 8, 7, 6, 5, 4, 3, 2, 1);
        Matrix3 r = m - n;

        CPPUNIT_ASSERT((-8 == r(1, 1)) && (-6 == r(1, 2)) && (-4 == r(1, 3)) &&
                       (-2 == r(2, 1)) && (0 == r(2, 2)) && (2 == r(2, 3)) &&
                       (4 == r(3, 1)) && (6 == r(3, 2)) && (8 == r(3, 3)));
    }

    void Matrix3_ut::test_add_equal_matrix()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(9, 8, 7, 6, 5, 4, 3, 2, 1);

        m += n;

        CPPUNIT_ASSERT((10 == m(1, 1)) && (10 == m(1, 2)) && (10 == m(1, 3)) &&
                       (10 == m(2, 1)) && (10 == m(2, 2)) && (10 == m(2, 3)) &&
                       (10 == m(3, 1)) && (10 == m(3, 2)) && (10 == m(3, 3)));
    }

    void Matrix3_ut::test_subtract_equal_matrix()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(9, 8, 7, 6, 5, 4, 3, 2, 1);

        m -= n;

        CPPUNIT_ASSERT((-8 == m(1, 1)) && (-6 == m(1, 2)) && (-4 == m(1, 3)) &&
                       (-2 == m(2, 1)) && (0 == m(2, 2)) && (2 == m(2, 3)) &&
                       (4 == m(3, 1)) && (6 == m(3, 2)) && (8 == m(3, 3)));
    }

    void Matrix3_ut::test_multiply_matrix()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(9, 8, 7, 6, 5, 4, 3, 2, 1);
        Matrix3 r = m * n;

        CPPUNIT_ASSERT((30 == r(1, 1)) && (24 == r(1, 2)) && (18 == r(1, 3)) &&
                       (84 == r(2, 1)) && (69 == r(2, 2)) && (54 == r(2, 3)) &&
                       (138 == r(3, 1)) && (114 == r(3, 2)) && (90 == r(3, 3)));
    }

    void Matrix3_ut::test_multiply_equal_matrix()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n(9, 8, 7, 6, 5, 4, 3, 2, 1);

        m *= n;

        CPPUNIT_ASSERT((30 == m(1, 1)) && (24 == m(1, 2)) && (18 == m(1, 3)) &&
                       (84 == m(2, 1)) && (69 == m(2, 2)) && (54 == m(2, 3)) &&
                       (138 == m(3, 1)) && (114 == m(3, 2)) && (90 == m(3, 3)));
    }

    void Matrix3_ut::test_multiply_vector()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Vec3<double> v(1, 2, 3);
        Vec3<double> r = m * v;

        CPPUNIT_ASSERT((14 == r(1)) && (32 == r(2)) && (50 == r(3)));
    }

    void Matrix3_ut::test_transpose()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);
        Matrix3 n = m.transpose();

        CPPUNIT_ASSERT((1 == n(1, 1)) && (4 == n(1, 2)) && (7 == n(1, 3)) &&
                       (2 == n(2, 1)) && (5 == n(2, 2)) && (8 == n(2, 3)) &&
                       (3 == n(3, 1)) && (6 == n(3, 2)) && (9 == n(3, 3)));
        CPPUNIT_ASSERT((1 == m(1, 1)) && (2 == m(1, 2)) && (3 == m(1, 3)) &&
                       (4 == m(2, 1)) && (5 == m(2, 2)) && (6 == m(2, 3)) &&
                       (7 == m(3, 1)) && (8 == m(3, 2)) && (9 == m(3, 3)));
    }

    void Matrix3_ut::test_inverse()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        /* m is initially a singular matrix, therefore, it's determinate should
         * be 0.
         */
        CPPUNIT_ASSERT(0 == m.determinant());
        CPPUNIT_ASSERT_THROW(m.inverse(), int);

        m(3, 3) = 0;
        Matrix3 n = m.inverse();
        Matrix3 r = (n * 10000) / 10000;

        DPRINTF("\n\n");
        for(int i = 1; i <= 3; ++i) {
            for(int j = 1; j <= 3; ++j) {
                r(i, j) = round(r(i, j) * 10000);
                DPRINTF("r(%d,%d) = %g%c", i, j, r(i, j),
                        (3 == j) ? '\n' : ' ');
            }
        }
        DPRINTF("\n");

        CPPUNIT_ASSERT(
            (-17778 == r(1, 1)) && (8889 == r(1, 2)) && (-1111 == r(1, 3)) &&
            (15556 == r(2, 1)) && (-7778 == r(2, 2)) && (2222 == r(2, 3)) &&
            (-1111 == r(3, 1)) && (2222 == r(3, 2)) && (-1111 == r(3, 3)));

        r = n.inverse();
        DPRINTF("\n\n");
        for(int i = 1; i <= 3; ++i) {
            for(int j = 1; j <= 3; ++j) {
                r(i, j) = round(r(i, j));
                DPRINTF("r(%d,%d) = %g%c", i, j, r(i, j),
                        (3 == j) ? '\n' : ' ');
            }
        }
        DPRINTF("\n");

        CPPUNIT_ASSERT(m == r);
    }

    void Matrix3_ut::test_determinant()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        /* m is initially a singular matrix, therefore, it's determinate should
         * be 0.
         */
        CPPUNIT_ASSERT(0 == m.determinant());

        /* Change m slightly so it's determinate is non-zero.
         */
        m(3, 3) = 0;
        CPPUNIT_ASSERT(27 == m.determinant());
        CPPUNIT_ASSERT(det(m) == m.determinant());
    }

    void Matrix3_ut::test_trace()
    {
        Matrix3 m(1, 2, 3, 4, 5, 6, 7, 8, 9);

        CPPUNIT_ASSERT(m.trace() == m(1, 1) + m(2, 2) + m(3, 3));
    }

} // namespace
