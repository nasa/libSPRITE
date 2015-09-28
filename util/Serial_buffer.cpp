#include <stdlib.h>

#include "util/Serial_buffer.h"
#include "base/assertion.h"
#include "base/byteswap.h"

namespace util {
    namespace {
        uint16_t (*swap16_)(uint16_t);
        uint32_t (*swap32_)(uint32_t);
        uint64_t (*swap64_)(uint64_t);
    }

    static uint16_t _nop16(uint16_t x)
    {
        return x;
    }

    static uint32_t _nop32(uint32_t x)
    {
        return x;
    }

    static uint64_t _nop64(uint64_t x)
    {
        return x;
    }

    static uint16_t _swap16(uint16_t x)
    {
        return byteswap16(x);
    }

    static uint32_t _swap32(uint32_t x)
    {
        return byteswap32(x);
    }

    static uint64_t _swap64(uint64_t x)
    {
        return byteswap64(x);
    }

    Serial_buffer::Serial_buffer(unsigned int maxSize)
        : m_buffer()
        , m_valid(false)
        , m_maxsize(maxSize)
        , m_pos(0)
        , m_blen(0)
        , m_nativeByteOrder((isbigendian()) ? BigEndian : LittleEndian)
        , m_byteOrder(m_nativeByteOrder)
    {
        /* Set the initial function pointers for btyeswapping to be a NOP.
         */
        swap16_ = _nop16;
        swap32_ = _nop32;
        swap64_ = _nop64;

        /* Allocate the buffer.
         */
        m_buffer.vptr = malloc(m_maxsize);
        m_valid = (m_buffer.vptr != NULL);
    }

    Serial_buffer::~Serial_buffer()
    {
        if(m_buffer.vptr != NULL) {
            free(m_buffer.vptr);
        }

        m_buffer.vptr = NULL;
    }

    void Serial_buffer::setByteOrder(ByteOrder order)
    {
        m_byteOrder = order;
        if(order == m_nativeByteOrder) {
            swap16_ = _nop16;
            swap32_ = _nop32;
            swap64_ = _nop64;
        } else {
            swap16_ = _swap16;
            swap32_ = _swap32;
            swap64_ = _swap64;
        }
    }

    void Serial_buffer::clear()
    {
        m_pos = m_blen = 0;
    }

    bool Serial_buffer::seek(unsigned int p)
    {
        if((false == m_valid) || (p >= m_maxsize)) {
            return false;
        }

        m_pos = p;

        return true;
    }

    bool Serial_buffer::get8(uint8_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        val = m_buffer.u8[m_pos];
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::put8(uint8_t val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        m_buffer.u8[m_pos] = val;
        m_pos += sizeof(val);
        m_blen = (m_pos > m_blen) ? m_pos : m_blen;

        return true;
    }

    bool Serial_buffer::get16(uint16_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        val = swap16_(*(p.u16));
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::put16(uint16_t val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        *(p.u16) = swap16_(val);
        m_pos += sizeof(val);
        m_blen = (m_pos > m_blen) ? m_pos : m_blen;

        return true;
    }

    bool Serial_buffer::get32(uint32_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        val = swap32_(*(p.u32));
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::put32(uint32_t val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        *(p.u32) = swap32_(val);
        m_pos += sizeof(val);
        m_blen = (m_pos > m_blen) ? m_pos : m_blen;

        return true;
    }

    bool Serial_buffer::get64(uint64_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        val = swap64_(*(p.u64));
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::put64(uint64_t val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val)))) {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        *(p.u64) = swap64_(val);
        m_pos += sizeof(val);
        m_blen = (m_pos > m_blen) ? m_pos : m_blen;

        return true;
    }

} // namespace isat_utils
