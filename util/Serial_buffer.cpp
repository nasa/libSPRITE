#include <stdlib.h>

#include "util/Serial_buffer.h"
#include "base/byteswap.h"

namespace util
{
    namespace
    {
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
        : m_maxsize(maxSize)
        , m_pos(0)
        , m_limit(0)
    {
        // Determine the byte order of the machine we're running on.
        m_nativeByteOrder = (isbigendian()) ? BigEndian : LittleEndian;
        m_byteOrder = m_nativeByteOrder;

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

    void Serial_buffer::setByteOrder(ByteOrder order)
    {
        m_byteOrder = order;
        if(order == m_nativeByteOrder)
        {
            swap16_ = _nop16;
            swap32_ = _nop32;
            swap64_ = _nop64;
        }
        else
        {
            swap16_ = _swap16;
            swap32_ = _swap32;
            swap64_ = _swap64;
        }
    }
#if 0
    Serial_buffer::Serial_buffer(Serial_buffer const &rhs)
    {
        cout << "Serial_buffer copy ctor\n";
        m_maxsize = rhs.maxSize;
        buffer = (char *)malloc(m_maxsize);
        memcpy(buffer, rhs.buffer, rhs.pos);

        nativeByteOrder = rhs.nativeByteOrder;
        byteOrder = rhs.byteOrder;

        pos = rhs.pos;
        limit = rhs.limit;
    }

    Serial_buffer &Serial_buffer::operator=(Serial_buffer rhs)
    {
        swapInstance(rhs);
        return *this;
    }

    Serial_buffer::~Serial_buffer()
    {
        if(buffer != 0)
            free(buffer);

        buffer = 0;
    }

    void Serial_buffer::swapInstance(Serial_buffer &rhs)
    {
        std::swap(buffer, rhs.buffer);
        std::swap(maxSize, rhs.maxSize);
        std::swap(pos, rhs.pos);
        std::swap(limit, rhs.limit);
        std::swap(byteOrder, rhs.byteOrder);
        std::swap(nativeByteOrder, rhs.nativeByteOrder);
    }
#endif

    void Serial_buffer::clear()
    {
        m_pos = 0;
        m_limit = 0;
    }

    bool Serial_buffer::seek(unsigned int p)
    {
        if((false == m_valid) || (p >= m_maxsize))
        {
            return false;
        }

        m_pos = p;

        return true;
    }

    void *Serial_buffer::getBytes()
    {
        return (true == m_valid) ? m_buffer.vptr : NULL;
    }

    bool Serial_buffer::put(const void *data, unsigned int nbytes)
    {
        if((false == m_valid) || (nbytes > (m_maxsize - m_pos)))
        {
            return false;
        }

        memcpy(&(m_buffer.u8[m_pos]), data, nbytes);
        m_pos += nbytes;

        return true;
    }

    bool Serial_buffer::get8(uint8_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
            return false;
        }

        val = m_buffer.u8[m_pos];
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::get16(uint16_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        val = swap16_(*(p.u16));
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::put8(uint8_t val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
            return false;
        }

        m_buffer.u8[m_pos] = val;
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::put16(uint16_t val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        *(p.u16) = swap16_(val);
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::get32(uint32_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
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
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        *(p.u32) = swap32_(val);
        m_pos += sizeof(val);

        return true;
    }

    bool Serial_buffer::get64(uint64_t &val)
    {
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
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
        if((false == m_valid) || (m_pos >= (m_maxsize - sizeof(val))))
        {
            return false;
        }

        Multi_ptr_t p;
        p.vptr = &m_buffer.u8[m_pos];

        *(p.u64) = swap64_(val);
        m_pos += sizeof(val);

        return true;
    }

#if 0 // Change this up to implement a single bit operation.
bool
Serial_buffer::putBoolean(bool val)
{
   if (pos < (maxSize - 1))
   {
      buffer[pos++] = val;

      if (pos > limit)
         limit = pos;

      return true;
   }

   return false;
}

    bool Serial_buffer::putShort(short val)
    {
        if(pos > int(maxSize - sizeof(short)))
            return false;

        if(byteOrder != nativeByteOrder)
            swap2((char *)&val);

        memcpy(&(buffer[pos]), &val, sizeof(short));
        pos = pos + sizeof(short);

        if(pos > limit)
            limit = pos;

        return true;
    }

    bool Serial_buffer::putInt(int val)
    {
        if(pos > int(maxSize - sizeof(int)))
            return false;

        if(byteOrder != nativeByteOrder)
            swap4((char *)&val);

        memcpy(&(buffer[pos]), &val, sizeof(int));
        pos = pos + sizeof(int);

        if(pos > limit)
            limit = pos;

        return true;
    }

    bool Serial_buffer::putFloat(float val)
    {
        if(pos > int(maxSize - sizeof(float)))
            return false;

        if(byteOrder != nativeByteOrder)
            swap4((char *)&val);

        memcpy(&(buffer[pos]), &val, sizeof(float));
        pos = pos + sizeof(float);

        if(pos > limit)
            limit = pos;

        return true;
    }

    bool Serial_buffer::putDouble(double val)
    {
        if(pos > int(maxSize - sizeof(double)))
            return false;

        if(byteOrder != nativeByteOrder)
            swap8((char *)&val);

        memcpy(&(buffer[pos]), &val, sizeof(double));
        pos = pos + sizeof(double);

        if(pos > limit)
            limit = pos;

        return true;
    }

#if 0
void
Serial_buffer::get(void* data, int length)
{

}
#endif

    bool Serial_buffer::getByte(unsigned char &val)
    {
        if(pos > int(maxSize - sizeof(unsigned char)))
            return false;

        val = buffer[pos];
        pos = pos + sizeof(unsigned char);

        return true;
    }

    bool Serial_buffer::getBoolean(bool &val)
    {
        val = false;

        if(pos < int(maxSize - sizeof(bool)))
        {
            val = buffer[pos++];
            return true;
        }

        return false;
    }

    bool Serial_buffer::getShort(short &val)
    {
        if(pos > int(maxSize - sizeof(short)))
            return false;

        val = 0;
        memcpy(&val, &(buffer[pos]), sizeof(short));
        pos = pos + sizeof(short);

        if(byteOrder != nativeByteOrder)
            swap2((char *)&val);

        return true;
    }

    bool Serial_buffer::getInt(int &val)
    {
        if(pos > int(maxSize - sizeof(int)))
            return false;

        val = 0;
        memcpy(&val, &(buffer[pos]), sizeof(int));
        pos = pos + sizeof(int);

        if(byteOrder != nativeByteOrder)
            swap4((char *)&val);

        return true;
    }

    bool Serial_buffer::getFloat(float &val)
    {

        if(pos > int(maxSize - sizeof(float)))
            return false;

        val = 0.0;
        memcpy(&val, &(buffer[pos]), sizeof(float));
        pos = pos + sizeof(float);

        if(byteOrder != nativeByteOrder)
            swap4((char *)&val);

        return true;
    }

    bool Serial_buffer::getDouble(double &val)
    {
        if(pos > int(maxSize - sizeof(double)))
            return false;

        val = 0.0;
        memcpy(&val, &(buffer[pos]), sizeof(double));
        pos = pos + sizeof(double);

        if(byteOrder != nativeByteOrder)
            swap8((char *)&val);

        return true;
    }

    bool Serial_buffer::getBits(int bitOffset, int bitWidth, int &value)
    {
        // XXX: Fix this. Remove bitfield size limitation.
        if(bitWidth > 56)
        {
            printf("Serial_buffer::getBits  bitfield too big! (bitWidth = %d)\n",
                   bitWidth);
            return false;
        }

        // Which bytes contain the bits we want?
        int startByte = bitOffset / 8;
        if((startByte < 0) || (startByte >= limit))
            return false;

        int endByte = (bitOffset + bitWidth - 1) / 8;
        if((endByte < 0) || (endByte >= limit))
            return false;

        // Put those bytes into a register (well, probably not really, but
        // putting them in a variable makes it easier to perform bit
        // operations on all of the bytes at the same time.
        long long bitbuf = 0;
        for(int i = startByte; i <= endByte; i++)
        {
            bitbuf = bitbuf << 8;
            bitbuf = bitbuf | (unsigned char)buffer[i];
        }

        // Move the bitfield we're trying to read to the extreme right
        // and chop off the unwanted part to the left. What remains is
        // the value we're after.
        bitbuf = bitbuf >> (7 - ((bitOffset + bitWidth - 1) % 8));
        bitbuf = bitbuf & ((1LL << bitWidth) - 1);

        value = bitbuf;

        return true;
    }

    bool Serial_buffer::putBits(int bitOffset, int bitWidth, int value)
    {
        // XXX: Fix this. Remove bitfield size limitation.
        if(bitWidth > 56)
        {
            printf("Serial_buffer::putBits  bitfield too big! (bitWidth = %d)\n",
                   bitWidth);
            return false;
        }

        // Can the value fit in the destination bitfield?
        if(((unsigned int)value) > ((1LL << bitWidth) - 1))
        {
            printf("value too large in putBits. value = %d, field width = %d\n",
                   value, bitWidth);
            return false;
        }

        // Which bytes contain the bits we want?
        int startByte = bitOffset / 8;
        if((startByte < 0) || (startByte >= limit))
            return false;

        int endByte = (bitOffset + bitWidth - 1) / 8;
        if((endByte < 0) || (endByte >= limit))
            return false;

        // Put those bytes into a register (well, probably not really, but
        // putting them in a variable makes it easier to perform bit
        // operations on all of the bytes at the same time.
        long long bitbuf = 0;
        for(int i = startByte; i <= endByte; i++)
        {
            bitbuf = bitbuf << 8;
            bitbuf = bitbuf | (unsigned char)buffer[i];
        }

        // Create a write mask that will be used to zero the bits in the
        // destination bitfield. Shift it left so it lines up with the
        // bitfield we're overwriting, and then negate it so we end up
        // with zeros at the bitfield locations and 1's everywhere else.
        // After and'ing with bitbuf, the bits in the destination bitfield are
        // all zero.
        long long writeMask = (1LL << bitWidth) - 1;
        writeMask = writeMask << 7 - ((bitOffset + bitWidth - 1) % 8);
        writeMask = ~writeMask;

        bitbuf = bitbuf & writeMask;

        // Shift the value to write to the left until it lines up with the
        // bitfield in bifbut.
        long long valbuf = value << (7 - ((bitOffset + bitWidth - 1) % 8));

        // "or" the value with bitbuf, writing it to the bitfield.
        bitbuf = bitbuf | valbuf;

        // Write the modified bytes back to the Serial_buffer's buffer.
        for(int i = endByte; i >= startByte; i--)
        {
            buffer[i] = bitbuf & 0xff;
            bitbuf = bitbuf >> 8;
        }

        return true;
    }
#endif

} // namespace isat_utils
