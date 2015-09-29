#include "util/Sample_set.h"
#include "util/Sample_set_ut.h"

namespace util {

    void Sample_set_ut::setUp()
    {
    }

    void Sample_set_ut::tearDown()
    {
    }

    void Sample_set_ut::test_int()
    {
        const unsigned int NELEM = 5;
        Sample_set<int> ss(NELEM);

        CPPUNIT_ASSERT_EQUAL(NELEM, ss.nelem());
        CPPUNIT_ASSERT_EQUAL(0u, ss.npopulated());

        ss.push(1);
        CPPUNIT_ASSERT_EQUAL(1u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(1, ss(1));

        ss.push(2);
        CPPUNIT_ASSERT_EQUAL(2u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(2, ss(1));
        CPPUNIT_ASSERT_EQUAL(1, ss(2));

        ss.push(3);
        CPPUNIT_ASSERT_EQUAL(3u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(3, ss(1));
        CPPUNIT_ASSERT_EQUAL(2, ss(2));
        CPPUNIT_ASSERT_EQUAL(1, ss(3));
        CPPUNIT_ASSERT_EQUAL(false, ss.is_full());

        ss.push(4);
        ss.push(5);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        ss.push(6);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        CPPUNIT_ASSERT_EQUAL(NELEM, ss.npopulated());

        CPPUNIT_ASSERT_EQUAL(6, ss(1));
        CPPUNIT_ASSERT_EQUAL(5, ss(2));
        CPPUNIT_ASSERT_EQUAL(4, ss(3));
        CPPUNIT_ASSERT_EQUAL(3, ss(4));
        CPPUNIT_ASSERT_EQUAL(2, ss(5));
    }

    void Sample_set_ut::test_double()
    {
        const unsigned int NELEM = 5;
        Sample_set<double> ss(NELEM);

        CPPUNIT_ASSERT_EQUAL(NELEM, ss.nelem());
        CPPUNIT_ASSERT_EQUAL(0u, ss.npopulated());

        ss.push(1.);
        CPPUNIT_ASSERT_EQUAL(1u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(1., ss(1));

        ss.push(2.);
        CPPUNIT_ASSERT_EQUAL(2u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(2., ss(1));
        CPPUNIT_ASSERT_EQUAL(1., ss(2));

        ss.push(3.);
        CPPUNIT_ASSERT_EQUAL(3u, ss.npopulated());
        CPPUNIT_ASSERT_EQUAL(3., ss(1));
        CPPUNIT_ASSERT_EQUAL(2., ss(2));
        CPPUNIT_ASSERT_EQUAL(1., ss(3));
        CPPUNIT_ASSERT_EQUAL(false, ss.is_full());

        ss.push(4.);
        ss.push(5.);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        ss.push(6.);
        CPPUNIT_ASSERT_EQUAL(true, ss.is_full());
        CPPUNIT_ASSERT_EQUAL(NELEM, ss.npopulated());

        CPPUNIT_ASSERT_EQUAL(6., ss(1));
        CPPUNIT_ASSERT_EQUAL(5., ss(2));
        CPPUNIT_ASSERT_EQUAL(4., ss(3));
        CPPUNIT_ASSERT_EQUAL(3., ss(4));
        CPPUNIT_ASSERT_EQUAL(2., ss(5));
    }

} // namespace
