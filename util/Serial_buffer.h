#ifndef __UTIL_SERIAL_BUFFER_H__
#define __UTIL_SERIAL_BUFFER_H__

#include "base/types.h"
#include "base/byteswap.h"

namespace util
{
    /**
     * A buffer of bytes with useful get/set methods.
     *
     * Modelled after Java's ByteBuffer class. This class wraps a
     * buffer of bytes and provides get and set methods for various
     * types commonly found in network packets. The byte order can be
     * switch back and forth, even between gets (some packet formats
     * have both big and little endian byte orders. Annoying.)
     *
     * The abstraction is a buffer with a maximum size and a current
     * read/write pointer. Reading or writing advances the pointer by
     * the size of whatever was read.
     */
    class Serial_buffer
    {
      public:
        /**
         * Create a serial buffer capable of holding up to maxsize bytes.
         */
        explicit Serial_buffer(unsigned int maxSize);
#if 0
        ~Serial_buffer();
#endif

        /**
         * Is the class valid.
         * @return true if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

        /**
         * Clears the buffer by resetting the read/write pointer to zero.
         * identical to seek(0).
         */
        void clear();

        /**
         * Move the read/write pointer to pos.
         */
        bool seek(unsigned int pos);

        /**
         * @return The current offset of the read/write pointer.
         */
        unsigned int getPosition() const
        {
            return m_pos;
        }

        unsigned int getLimit() const
        {
            return m_limit;
        }

        unsigned int getCapacity() const
        {
            return m_maxsize;
        }

        void setByteOrder(ByteOrder order);

        ByteOrder getByteOrder() const
        {
            return m_byteOrder;
        }

        ByteOrder getNativeByteOrder() const
        {
            return m_nativeByteOrder;
        }

        /**
         * Return a pointer to the raw bytes in this instance.
         */
        void *getBytes();

        /**
         * Write length bytes from data into this instance's buffer.
         */
        bool put(const void *data, unsigned int nbytes);

        bool put8(uint8_t val);

        bool put16(uint16_t val);

        bool put32(uint32_t val);

        bool put64(uint64_t val);

#if 0
        // bool get(char*& data, int length);
#endif

        bool get8(uint8_t &val);

        bool get16(uint16_t &value);

        bool get32(uint32_t &value);

        bool get64(uint64_t &value);

#if 0
        // The following methods allow direct access to bit fields within the
        // byte buffer.
        // There is no concept of a position or a seek, the bit offset and field
        // size is
        // specified in the call to the method.

        bool getBits(int bitOffset, int bitWidth, int &value);

        bool putBits(int bitOffset, int bitWidth, int value);
#endif

      private:
        /* Disable copy and assignment constructors.
         */
        Serial_buffer(Serial_buffer const &rhs);
        Serial_buffer &operator=(Serial_buffer rhs);

        /**
         * Declare the storage buffer as a union of many different types of
         * pointers so we can easily access different data types.
         */
        union Multi_ptr_t
        {
            void *vptr;
            uint8_t *u8;
            uint16_t *u16;
            uint32_t *u32;
            uint64_t *u64;
        };

        Multi_ptr_t m_buffer;

        bool m_valid;
        const unsigned int m_maxsize;
        unsigned int m_pos;
        unsigned int m_limit;

        ByteOrder m_byteOrder;
        ByteOrder m_nativeByteOrder;

#if 0
        void swapInstance(Serial_buffer &rhs);
#endif
    };

} // namespace

#endif // __UTIL_SERIAL_BUFFER_H__
