#include "units/Kilometers.h"
#include "units/Millimeters.h"
#include "units/Meters.h"
#include "Meters_ut.h"
#include "base/XPRINTF.h"

namespace units {

    void Meters_ut::setUp()
    {
    }

    void Meters_ut::tearDown()
    {
    }

    void Meters_ut::test()
    {
        const double KILOMETERS_PER_METER = 0.001;
        const double EPSILON = 1e-12;

        Meters m(1.0);
        Kilometers km(KILOMETERS_PER_METER);

        CPPUNIT_ASSERT_EQUAL(m, Meters(km));

        CPPUNIT_ASSERT_DOUBLES_EQUAL(KILOMETERS_PER_METER, m.toKilometers(),
                                     EPSILON);

        m = Meters(2 * 3);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(6.0, m, EPSILON);

        m = Meters(4.0 / 2);

        CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, m, EPSILON);
    }

    void Meters_ut::test_millimeters()
    {
        const double MILLIMETERS_PER_METER = 1000;
        const double EPSILON = 1e-12;

        Meters m(1.0);
        Millimeters mm(MILLIMETERS_PER_METER);

        CPPUNIT_ASSERT_EQUAL(m, Meters(mm));

        CPPUNIT_ASSERT_DOUBLES_EQUAL(MILLIMETERS_PER_METER, m.toMillimeters(),
                                     EPSILON);
    }

} // namespace
