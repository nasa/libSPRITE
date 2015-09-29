#include "units/Meters.h"
#include "units/Millimeters.h"
#include "units/Millimeters_ut.h"
#include "base/XPRINTF.h"

namespace units {

    void Millimeters_ut::setUp()
    {
    }

    void Millimeters_ut::tearDown()
    {
    }

    void Millimeters_ut::test()
    {
        Millimeters mm(2 * 3);

        CPPUNIT_ASSERT_EQUAL((int64_t)6, int64_t(mm));

        mm = Millimeters(4 / 2);

        CPPUNIT_ASSERT_EQUAL(units::Millimeters(2), mm);
    }

    void Millimeters_ut::test_meters()
    {
        const units::Millimeters MILLIMETERS_PER_METER(1000);

        Millimeters mm(1);
        Meters m(1.0);

        CPPUNIT_ASSERT_EQUAL(MILLIMETERS_PER_METER, Millimeters(m));

        CPPUNIT_ASSERT_EQUAL(MILLIMETERS_PER_METER, m.toMillimeters());
    }

} // namespace
