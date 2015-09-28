#include "util/Serial_buffer.h"
#include "util/Serial_buffer_ut.h"

#include "base/XPRINTF.h"

namespace util {
    Serial_buffer_ut::Serial_buffer_ut()
    {
    }

    void Serial_buffer_ut::setUp()
    {
    }

    void Serial_buffer_ut::tearDown()
    {
    }

    void Serial_buffer_ut::test_serdes()
    {
        const unsigned int CAPACITY = 10;
        Serial_buffer buf(CAPACITY);
        ByteOrder native_order = buf.getNativeByteOrder();

        /* Check initial state.
         */
        CPPUNIT_ASSERT_EQUAL(true, buf.is_valid());
        CPPUNIT_ASSERT_EQUAL(0U, buf.getPosition());
        CPPUNIT_ASSERT_EQUAL(CAPACITY, buf.getCapacity());
        CPPUNIT_ASSERT_EQUAL(0U, buf.getBufferLength());

        /* Put some data.
         */
        uint8_t value8 = 0x01U;
        CPPUNIT_ASSERT_EQUAL(true, buf.put8(value8++));
        CPPUNIT_ASSERT_EQUAL(true, buf.put8(value8++));
        CPPUNIT_ASSERT_EQUAL(2U, buf.getPosition());
        CPPUNIT_ASSERT_EQUAL(2U, buf.getBufferLength());

        /* Seek to the begining and and test the written values.
         */
        uint8_t expected_value8 = 0x01;
        buf.seek(0);
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8++, value8);
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8++, value8);

        /* Seek to the end and try to put data. Should fail.
         */
        CPPUNIT_ASSERT_EQUAL(true, buf.seek(CAPACITY - 1));
        CPPUNIT_ASSERT_EQUAL(false, buf.put8(value8));

        /* Try to seek past the end of the buffer.
         */
        CPPUNIT_ASSERT_EQUAL(false, buf.seek(CAPACITY));

        /* Try some 16 bit values.
         */
        uint16_t value16 = 0xA55AU;
        uint16_t expected_value16 = value16;

        // Puts
        buf.clear();
        CPPUNIT_ASSERT_EQUAL(true, buf.seek(CAPACITY - 8));
        CPPUNIT_ASSERT_EQUAL(true, buf.put16(value16));
        ++value16;

        buf.setByteOrder(LittleEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.put16(value16));
        ++value16;

        buf.setByteOrder(BigEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.put16(value16));
        ++value16;

        // Runs off the end of buffer. Should fail.
        CPPUNIT_ASSERT_EQUAL(false, buf.put16(value16));

        // Gets
        buf.setByteOrder(native_order);
        CPPUNIT_ASSERT_EQUAL(true, buf.seek(CAPACITY - 8));
        CPPUNIT_ASSERT_EQUAL(true, buf.get16(value16));
        CPPUNIT_ASSERT_EQUAL(expected_value16, value16);
        ++expected_value16;

        buf.setByteOrder(LittleEndian);
        // buf.setByteOrder((LittleEndian == native_order) ? BigEndian :
        // LittleEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.get16(value16));
        CPPUNIT_ASSERT_EQUAL(expected_value16, value16);
        CPPUNIT_ASSERT_EQUAL(true, buf.seek(buf.getPosition() - 2));
        expected_value8 = expected_value16 & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = (expected_value16 >> 8) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        ++expected_value16;

        buf.setByteOrder(BigEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.get16(value16));
        CPPUNIT_ASSERT_EQUAL(expected_value16, value16);
        CPPUNIT_ASSERT_EQUAL(true, buf.seek(buf.getPosition() - 2));
        expected_value8 = (expected_value16 >> 8) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = expected_value16 & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        ++expected_value16;

        buf.setByteOrder(native_order);

        // Runs off the end of buffer. Should fail.
        CPPUNIT_ASSERT_EQUAL(false, buf.get16(value16));

        /* Try some 32 bit values.
         */
        uint32_t value32 = 0x11223344U;
        uint32_t expected_value32 = value32;

        // Puts
        buf.clear();
        buf.setByteOrder(LittleEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.put32(value32));
        ++value32;

        buf.setByteOrder(BigEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.put32(value32));
        ++value32;

        // Runs off the end of buffer. Should fail.
        CPPUNIT_ASSERT_EQUAL(false, buf.put32(value32));

        // Gets
        buf.seek(0);
        buf.setByteOrder(LittleEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.get32(value32));
        CPPUNIT_ASSERT_EQUAL(expected_value32, value32);
        CPPUNIT_ASSERT_EQUAL(true, buf.seek(buf.getPosition() - 4));
        expected_value8 = expected_value32 & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = (expected_value32 >> 8) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = (expected_value32 >> 16) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = (expected_value32 >> 24) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        ++expected_value32;

        buf.setByteOrder(BigEndian);
        CPPUNIT_ASSERT_EQUAL(true, buf.get32(value32));
        CPPUNIT_ASSERT_EQUAL(expected_value32, value32);
        CPPUNIT_ASSERT_EQUAL(true, buf.seek(buf.getPosition() - 4));
        expected_value8 = (expected_value32 >> 24) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = (expected_value32 >> 16) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = (expected_value32 >> 8) & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        expected_value8 = expected_value32 & 0xFF;
        CPPUNIT_ASSERT_EQUAL(true, buf.get8(value8));
        CPPUNIT_ASSERT_EQUAL(expected_value8, value8);
        ++expected_value32;

        buf.setByteOrder(native_order);

        // Runs off the end of buffer. Should fail.
        CPPUNIT_ASSERT_EQUAL(false, buf.get32(value32));

        /* Test buffer length.
         */
        CPPUNIT_ASSERT_EQUAL(8U, buf.getBufferLength());

        /* Test getting the buffer address and look for the expected values.
         */
        uint32_t *bptr = static_cast<uint32_t *>(buf.getAddr());
        value32 =
            (LittleEndian == native_order) ? bptr[0] : byteswap32(bptr[0]);
        CPPUNIT_ASSERT_EQUAL(expected_value32 - 2, value32);
        value32 = (BigEndian == native_order) ? bptr[1] : byteswap32(bptr[1]);
        CPPUNIT_ASSERT_EQUAL(expected_value32 - 1, value32);

        /* Try some 64 bit values.
         */
        uint64_t value64 = 0x1122334455667788U;
        uint64_t expected_value64 = value64;

        // Puts
        buf.clear();
        CPPUNIT_ASSERT_EQUAL(true, buf.put64(value64));

        // Runs off the end of buffer. Should fail.
        CPPUNIT_ASSERT_EQUAL(false, buf.get64(value64));

        // Gets
        buf.seek(0);
        CPPUNIT_ASSERT_EQUAL(true, buf.get64(value64));
        CPPUNIT_ASSERT_EQUAL(expected_value64, value64);

        // Runs off the end of buffer. Should fail.
        CPPUNIT_ASSERT_EQUAL(false, buf.get64(value64));
    }

} // namespace
