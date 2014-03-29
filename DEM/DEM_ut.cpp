// $Id$

#include <string.h>
#include "DEM_ut.h"
#include "base/XPRINTF.h"


namespace DEM
{

    void DEM_ut::setUp()
    {
        dem = new(DEM);
    }


    void DEM_ut::tearDown()
    {
        delete(dem);
    }


    void DEM_ut::test_get_header_size()
    {
        dem->header.clear_sequence_counter_present();
        CPPUNIT_ASSERT(16 == dem->get_header_size());
        dem->header.set_sequence_counter_present();
        CPPUNIT_ASSERT(18 == dem->get_header_size());
    }


    void DEM_ut::test_get_payload_size()
    {
        const unsigned int psize = 17;
        dem->header.clear_sequence_counter_present();
        dem->header.set_size(dem->get_header_size() + psize + DEM_CRC_SIZE);
        CPPUNIT_ASSERT(psize == dem->get_payload_size());
        dem->header.set_sequence_counter_present();
        dem->header.set_size(dem->get_header_size() + psize + DEM_CRC_SIZE);
        CPPUNIT_ASSERT(psize == dem->get_payload_size());
    }


    void DEM_ut::test_get_payload_pointer()
    {
        dem->header.set_sequence_counter_present();
        unsigned int payload_start = dem->get_header_size();
        uint8_t* p = dem->get_payload_pointer();
        CPPUNIT_ASSERT(18 == payload_start);
        dem->byte[payload_start] = 0x5A;
        CPPUNIT_ASSERT(0x5A == p[0]);
        dem->byte[payload_start] = 0xA5;
        CPPUNIT_ASSERT(0xA5 == p[0]);

        dem->header.clear_sequence_counter_present();
        payload_start = dem->get_header_size();
        p = dem->get_payload_pointer();
        CPPUNIT_ASSERT(16 == payload_start);
    }


    void DEM_ut::test_get_crc_offset()
    {
        const uint16_t dem_size = 41;
        dem->header.set_size(dem_size);
        unsigned int crc_start = dem->get_crc_offset();
        CPPUNIT_ASSERT(crc_start == dem_size - DEM_CRC_SIZE);
    }


    void DEM_ut::test_get_crc()
    {
        const uint16_t dem_size = 40;
        dem->header.set_size(dem_size);
        unsigned int crc_start = dem->get_crc_offset();
        const uint32_t crc_value = 0xA55AC44C;
        dem->byte[crc_start] = crc_value >> 24;
        dem->byte[crc_start + 1] = (crc_value >> 16) & 0xFF;
        dem->byte[crc_start + 2] = (crc_value >> 8) & 0xFF;
        dem->byte[crc_start + 3] = crc_value & 0xFF;

        dem->header.set_crc_present();
        CPPUNIT_ASSERT(crc_value == dem->get_crc());
        dem->header.clear_crc_present();
        CPPUNIT_ASSERT(0 == dem->get_crc());
    }


    void DEM_ut::test_set_crc()
    {
        const uint16_t dem_size = 39;
        dem->header.set_size(dem_size);
        unsigned int crc_start = dem->get_crc_offset();
        const uint32_t crc_value = 0xA55AC44C;
        dem->byte[crc_start] = dem->byte[crc_start + 1] =
            dem->byte[crc_start + 2] = dem->byte[crc_start + 3] = 0;

        dem->header.set_crc_present();
        dem->set_crc(crc_value);
        CPPUNIT_ASSERT(dem->byte[crc_start] == (crc_value >> 24));
        CPPUNIT_ASSERT(dem->byte[crc_start + 1] == ((crc_value >> 16) & 0xFF));
        CPPUNIT_ASSERT(dem->byte[crc_start + 2] == ((crc_value >> 8) & 0xFF));
        CPPUNIT_ASSERT(dem->byte[crc_start + 3] == (crc_value & 0xFF));
    }


    void DEM_ut::test_crc()
    {
        memset(dem, 0, sizeof(*dem));
        dem->header.set_crc_present();
        dem->header.set_size(dem->get_header_size() + DEM_CRC_SIZE);
#if 0
        unsigned int s = dem->get_header_size();
        for(unsigned int i = 0; i < s; ++i)
        {
            DPRINTF("%x ", dem->byte[i]);
        }
        DPRINTF("\n");

        uint32_t crc = dem->calculate_crc();
        DPRINTF("crc = %#x\n", crc);
#endif
        CPPUNIT_ASSERT(0x44178d15 == dem->calculate_crc());
        dem->set_crc(0x44178d15);
        CPPUNIT_ASSERT(dem->crc_is_valid());
        dem->header.set_content_id(27);
        dem->update_crc();
        CPPUNIT_ASSERT(0x6a8251b9 == dem->calculate_crc());
        CPPUNIT_ASSERT(dem->crc_is_valid());
        CPPUNIT_ASSERT(dem->get_crc() == dem->calculate_crc());
    }

} // namespace
