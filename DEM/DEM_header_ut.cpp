#include "DEM/DEM_header_ut.h"
#include "DEM/Timestamp.h"
#include "base/XPRINTF.h"


namespace DEM
{

    void DEM_header_ut::setUp()
    {
        header = new(DEM_header);
        byte = (uint8_t*)header;
    }


    void DEM_header_ut::tearDown()
    {
        delete(header);
    }


    void DEM_header_ut::test_size()
    {
        const uint16_t size = 0x5aa5;
        header->set_size(size);
        CPPUNIT_ASSERT(size == header->get_size());
        CPPUNIT_ASSERT(0x5a == byte[0]);
        CPPUNIT_ASSERT(0xa5 == byte[1]);
    }


    void DEM_header_ut::test_version_number()
    {
        const unsigned int v = 3;
        byte[2] = 0xFF;
        header->set_version_number(v);
        CPPUNIT_ASSERT(v == header->get_version_number());
        CPPUNIT_ASSERT(0x7F == byte[2]);
        byte[2] = 0x00;
        header->set_version_number(v);
        CPPUNIT_ASSERT(v == header->get_version_number());
        CPPUNIT_ASSERT(0x60 == byte[2]);
    }


    void DEM_header_ut::test_crc_is_present()
    {
        byte[2] = 0;
        header->set_crc_present();
        CPPUNIT_ASSERT(true == header->crc_is_present());
        CPPUNIT_ASSERT(0x10 == byte[2]);
        header->clear_crc_present();
        CPPUNIT_ASSERT(false == header->crc_is_present());
        CPPUNIT_ASSERT(0x00 == byte[2]);
    }


    void DEM_header_ut::test_sequence_counter_is_present()
    {
        byte[3] = 0;
        header->set_sequence_counter_present();
        CPPUNIT_ASSERT(true == header->sequence_counter_is_present());
        CPPUNIT_ASSERT(0x80 == byte[3]);
        header->clear_sequence_counter_present();
        CPPUNIT_ASSERT(false == header->sequence_counter_is_present());
        CPPUNIT_ASSERT(0x00 == byte[3]);
    }


    void DEM_header_ut::test_secondary_header_is_present()
    {
        byte[3] = 0;
        header->set_secondary_header_present();
        CPPUNIT_ASSERT(true == header->secondary_header_is_present());
        CPPUNIT_ASSERT(0x40 == byte[3]);
        header->clear_secondary_header_present();
        CPPUNIT_ASSERT(false == header->secondary_header_is_present());
        CPPUNIT_ASSERT(0x00 == byte[3]);
    }


    void DEM_header_ut::test_origin_code()
    {
        byte[3] = 0xFF;
        header->set_origin_code(DEM_ORIGIN_TEST);
        CPPUNIT_ASSERT(DEM_ORIGIN_TEST == header->get_origin_code());
        CPPUNIT_ASSERT(0xD7 == byte[3]);
        byte[3] = 0x00;
        header->set_origin_code(DEM_ORIGIN_REPLAY);
        CPPUNIT_ASSERT(DEM_ORIGIN_REPLAY == header->get_origin_code());
        CPPUNIT_ASSERT(0x08 == byte[3]);
    }


    void DEM_header_ut::test_operation_code()
    {
        byte[3] = 0xFF;
        header->set_operation_code(DEM_OPERATION_MSG);
        CPPUNIT_ASSERT(DEM_OPERATION_MSG == header->get_operation_code());
        CPPUNIT_ASSERT(0xF9 == byte[3]);
        byte[3] = 0x00;
        header->set_operation_code(DEM_OPERATION_MSG_RSP);
        CPPUNIT_ASSERT(DEM_OPERATION_MSG_RSP == header->get_operation_code());
        CPPUNIT_ASSERT(0x03 == byte[3]);
    }


    void DEM_header_ut::test_system_id()
    {
        byte[4] = byte[5] = 0xFF;
        header->set_system_id(DEM_SYSTEM_ID_ARES);
        CPPUNIT_ASSERT(DEM_SYSTEM_ID_ARES == header->get_system_id());
        CPPUNIT_ASSERT(0x00 == byte[4]);
        CPPUNIT_ASSERT(0x3F == byte[5]);
        byte[4] = byte[5] = 0x00;
        header->set_system_id(DEM_SYSTEM_ID_GS);
        CPPUNIT_ASSERT(DEM_SYSTEM_ID_GS == header->get_system_id());
        CPPUNIT_ASSERT(0x00 == byte[4]);
        CPPUNIT_ASSERT(0x40 == byte[5]);
    }


    void DEM_header_ut::test_type_id()
    {
        byte[5] = 0xFF;
        header->set_type_id(DEM_TYPE_COMMAND);
        CPPUNIT_ASSERT(DEM_TYPE_COMMAND == header->get_type_id());
        CPPUNIT_ASSERT(0xE1 == byte[5]);
        byte[5] = 0x00;
        header->set_type_id(DEM_TYPE_TELEMETRY);
        CPPUNIT_ASSERT(DEM_TYPE_TELEMETRY == header->get_type_id());
        CPPUNIT_ASSERT(0x02 == byte[5]);
    }


    void DEM_header_ut::test_content_id()
    {
        const uint16_t c = 0x5aa5;
        header->set_content_id(c);
        CPPUNIT_ASSERT(c == header->get_content_id());
        CPPUNIT_ASSERT(0x5a == byte[6]);
        CPPUNIT_ASSERT(0xa5 == byte[7]);
    }


    void DEM_header_ut::test_get_timestamp()
    {
        DEM_timestamp ts = header->get_timestamp();
        ts.set_seconds(12345);
        ts.set_milliseconds(123);
        double t = ts.get_time();
        CPPUNIT_ASSERT(t > 12345.122);
        CPPUNIT_ASSERT(t < 12345.124);
    }


    void DEM_header_ut::test_set_timestamp()
    {
        DEM_timestamp ts;
        ts.set_seconds(12345);
        ts.set_milliseconds(123);
        header->set_timestamp(ts);
        double t = ts.get_time();
        CPPUNIT_ASSERT(t > 12345.122);
        CPPUNIT_ASSERT(t < 12345.124);
    }


    void DEM_header_ut::test_timestamp_class()
    {
        Timestamp ts(12345, 123);

        header->set_timestamp(ts);
        double t = ts.get_time();
        CPPUNIT_ASSERT(t > 12345.122);
        CPPUNIT_ASSERT(t < 12345.124);
    }


    void DEM_header_ut::test_source_system_id()
    {
        byte[14] = byte[15] = 0xFF;
        header->set_source_system_id(DEM_SYSTEM_ID_ARES);
        CPPUNIT_ASSERT(DEM_SYSTEM_ID_ARES == header->get_source_system_id());
        CPPUNIT_ASSERT(0x00 == byte[14]);
        CPPUNIT_ASSERT(0x3F == byte[15]);
        byte[14] = byte[15] = 0x00;
        header->set_source_system_id(DEM_SYSTEM_ID_GS);
        CPPUNIT_ASSERT(DEM_SYSTEM_ID_GS == header->get_source_system_id());
        CPPUNIT_ASSERT(0x00 == byte[14]);
        CPPUNIT_ASSERT(0x40 == byte[15]);
    }


    void DEM_header_ut::test_source_subsystem_id()
    {
        const uint16_t ssid = 0x1F;
        byte[15] = 0xFF;
        header->set_source_subsystem_id(ssid);
        CPPUNIT_ASSERT(ssid == header->get_source_subsystem_id());
        CPPUNIT_ASSERT(0xFF == byte[15]);
        byte[15] = 0x00;
        header->set_source_subsystem_id(ssid);
        CPPUNIT_ASSERT(ssid == header->get_source_subsystem_id());
        CPPUNIT_ASSERT(0x1F == byte[15]);
    }


    void DEM_header_ut::test_source_system_subsystem()
    {
        const uint16_t ssid = 0x08;
        byte[14] = byte[15] = 0x00;
        header->set_source_system_id(DEM_SYSTEM_ID_ARES);
        header->set_source_subsystem_id(ssid);
        CPPUNIT_ASSERT_EQUAL(DEM_SYSTEM_ID_ARES, header->get_source_system_id());
        CPPUNIT_ASSERT_EQUAL((unsigned int) ssid, header->get_source_subsystem_id());
        CPPUNIT_ASSERT_EQUAL(0x0028, (int) header->get_source_system_subsystem());
//        CPPUNIT_ASSERT_EQUAL(0x28, byte[14]);
//        CPPUNIT_ASSERT_EQUAL(0x01, byte[15]);
    }


    void DEM_header_ut::test_sequence_count()
    {
        const uint16_t c = 0x5aa5;
        header->set_sequence_counter_present();
        header->set_sequence_count(c);
        CPPUNIT_ASSERT(c == header->get_sequence_count());
        CPPUNIT_ASSERT(0x5a == byte[16]);
        CPPUNIT_ASSERT(0xa5 == byte[17]);
        header->clear_sequence_counter_present();
        header->set_sequence_count(~c);
        CPPUNIT_ASSERT(0 == header->get_sequence_count());
        CPPUNIT_ASSERT(0x5a == byte[16]);
        CPPUNIT_ASSERT(0xa5 == byte[17]);
    }

} // namespace
