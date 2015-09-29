#include "units/Celsius.h"
#include "units/Celsius_ut.h"

namespace units {

    void Celsius_ut::setUp()
    {
    }

    void Celsius_ut::tearDown()
    {
    }

    void Celsius_ut::test()
    {
        Celsius zero;
        CPPUNIT_ASSERT_EQUAL(0.0, double(zero));

        const double epsilon = 1e-12;

        const double da = 2.1;
        const double db = 3.2;
        Celsius a(da);
        Celsius b(db);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(-da, -a, epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(da + db, a + b, epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(da - db, a - b, epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(da * db, a * b, epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(da / db, a / b, epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(da + db, a += b, epsilon);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(da, a -= b, epsilon);
    }

} // namespace
