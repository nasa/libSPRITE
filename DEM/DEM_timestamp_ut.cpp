// $Id$

#include "DEM_timestamp_ut.h"
#include "base/XPRINTF.h"
#include "units/Nanoseconds.h"
#include "units/Seconds.h"


namespace DEM
{

    void DEM_timestamp_ut::setUp()
    {
        ts = new(DEM_timestamp);
        byte = (uint8_t *) ts;
    }


    void DEM_timestamp_ut::tearDown()
    {
        delete(ts);
    }


    void DEM_timestamp_ut::test_seconds()
    {
        const uint32_t seconds = 0x5AA53CC3;
        ts->set_seconds(seconds);
        uint32_t s = ts->get_seconds();
        CPPUNIT_ASSERT(s == seconds);
        CPPUNIT_ASSERT(0x5A == byte[0]);
        CPPUNIT_ASSERT(0xA5 == byte[1]);
        CPPUNIT_ASSERT(0x3C == byte[2]);
        CPPUNIT_ASSERT(0xC3 == byte[3]);
    }


    void DEM_timestamp_ut::test_milliseconds()
    {
        byte[4] = byte[5] = 0xFF;
        const uint16_t ms1= 1;
        ts->set_milliseconds(ms1);
        CPPUNIT_ASSERT(ms1 == ts->get_milliseconds());
        CPPUNIT_ASSERT(0x00 == byte[4]);
        CPPUNIT_ASSERT(0x7F == byte[5]);
        byte[4] = byte[5] = 0x00;
        const uint16_t ms2= 999;
        ts->set_milliseconds(ms2);
        CPPUNIT_ASSERT(ms2== ts->get_milliseconds());
        CPPUNIT_ASSERT(0xF9 == byte[4]);
        CPPUNIT_ASSERT(0xC0 == byte[5]);
    }


    void DEM_timestamp_ut::test_get_time()
    {
        ts->set_seconds(12345678);
        ts->set_milliseconds(123);
        double t = ts->get_time();
        CPPUNIT_ASSERT((t > 12345678.122) && (t < 12345678.124));
    }


    void DEM_timestamp_ut::test_relational_operators()
    {
        DEM_timestamp ts2;
        ts2.set_seconds(12345678);
        ts2.set_milliseconds(0);
        ts->set_seconds(12345678);
        ts->set_milliseconds(0);
        CPPUNIT_ASSERT(*ts == ts2);
        ts2.set_seconds(12341234);
        CPPUNIT_ASSERT(*ts != ts2);
        ts2.set_seconds(12345678);
        ts2.set_milliseconds(123);
        CPPUNIT_ASSERT(*ts != ts2);
    }


    void DEM_timestamp_ut::test_nanoseconds()
    {
        units::Nanoseconds nano(units::Seconds(1.2001));
        *ts = nano;

        CPPUNIT_ASSERT_EQUAL(1, (int)ts->get_seconds());
        CPPUNIT_ASSERT_EQUAL(200, (int)ts->get_milliseconds());
    }

} // namespace
