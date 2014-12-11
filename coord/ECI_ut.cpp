#include "coord/ECI.h"
#include "coord/ECI_ut.h"
#include "coord/GST_angle.h"
#include "units/Meters.h"
#include "units/J2010_time.h"
#include <stdio.h>


namespace coord
{

    void ECI_ut::setUp()
    {
    }


    void ECI_ut::tearDown()
    {
    }


    void ECI_ut::test_position_constructor()
    {
        ECI<units::Meters> eci(units::Meters(10.0), units::Meters(20.0),
                units::Meters(30.0));

        CPPUNIT_ASSERT_EQUAL(units::Meters(10.0), eci(1));
        CPPUNIT_ASSERT_EQUAL(units::Meters(20.0), eci(2));
        CPPUNIT_ASSERT_EQUAL(units::Meters(30.0), eci(3));
    }


    void ECI_ut::test_position_vector_constructor()
    {
        ECI<units::Meters> eci(math::Vec3<units::Meters>(10.0, 20.0, 30.0));

        CPPUNIT_ASSERT_EQUAL(units::Meters(10.0), eci(1));
        CPPUNIT_ASSERT_EQUAL(units::Meters(20.0), eci(2));
        CPPUNIT_ASSERT_EQUAL(units::Meters(30.0), eci(3));
    }


    void ECI_ut::test_toECEF()
    {
        ECI<units::Meters> eci(math::Vec3<units::Meters>(
                    20000.0, 4000.0, 5000.0));
        units::J2000_time t(0);
        units::Radians gst(calculate_GST_angle(t));
        ECEF<units::Meters> ecef = eci.toECEF(gst);

        /* Using test values determined from ECItoECEF Matlab script.
         */
        math::Vec3<units::Meters> ex(-303.50, 20393.82, 5000.0);
        const units::Meters eps(0.2);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(1), ecef(1), eps);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(2), ecef(2), eps);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(3), ecef(3), eps);

        units::J2010_time t2010(0);
        t = units::J2000_time(t2010);
        gst = calculate_GST_angle(t);
        ecef = eci.toECEF(gst);

        ex = math::Vec3<units::Meters>(273.61, -20394.24, 5000.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(1), ecef(1), eps);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(2), ecef(2), eps);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(3), ecef(3), eps);

        // May 8, 2012 18:00
        t = units::J2000_time(4511.25);
        gst = calculate_GST_angle(t);
        ecef = eci.toECEF(gst);

        ex = math::Vec3<units::Meters>(-11889.10, -16572.54, 5000.0);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(1), ecef(1), eps);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(2), ecef(2), eps);
        CPPUNIT_ASSERT_DOUBLES_EQUAL(ex(3), ecef(3), eps);

    }

} // namespace
