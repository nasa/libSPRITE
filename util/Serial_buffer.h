#ifndef __UTIL_SERIAL_BUFFER_H__
#define __UTIL_SERIAL_BUFFER_H__

#include "base/types.h"
#include "base/byteswap.h"

namespace util {
    /**
     * A buffer of bytes with useful get/set methods.
     *
     * This class is used to serialize and deserialize data in/out of a buffer.
     * Byteswapping is handling within this class. The byte order can switch
     * back and forth, even between get/put operations to support some packet
     * formats that have both big and little endian byte orders.
     *
     * The abstraction is a buffer with a maximum size and a current
     * read/write pointer. Reading or writing advances the pointer by
     * the size of whatever was read.
     */
    class Serial_buffer {
      public:
        /**
         * Create a serial buffer capable of holding up to maxsize bytes.
         * @param maxSize Maximum size of the buffer.
         */
        explicit Serial_buffer(unsigned int maxSize);

        /**
         * Destructor.
         */
        ~Serial_buffer();

        /**
         * Is the class valid.
         * @return true if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

        /**
         * Get the starting address of the buffer.
         * @param Buffer starting address.
         */
        void *getAddr()
        {
            return m_buffer.vptr;
        }

        /**
         * Clears the buffer by resetting the read/write pointer to zero and
         * setting the buffer length to 0.
         */
        void clear();

        /**
         * Move the read/write pointer to pos.
         * @param pos Offset into the buffer in number of bytes to seek to.
         * @return True on success, else false.
         */
        bool seek(unsigned int pos);

        /**
         * Get the current offset of the read/write pointer.
         * @return The current offset of the read/write pointer.
         */
        unsigned int getPosition() const
        {
            return m_pos;
        }

        /**
         * Return the size of the buffer.
         * @return maximum size of the buffer.
         */
        unsigned int getCapacity() const
        {
            return m_maxsize;
        }

        /**
         * Return the number of bytes that have been used in the buffer.
         * @return Number of bytes in use.
         */
        unsigned int getBufferLength() const
        {
            return m_blen;
        }

        /**
         * Set the endian order of the buffer for all future get/put operations.
         * @param order big or little endian.
         */
        void setByteOrder(ByteOrder order);

        ByteOrder getByteOrder() const
        {
            return m_byteOrder;
        }

        /**
         * Get this machines native byte order.
         * @return native byte order.
         */
        ByteOrder getNativeByteOrder() const
        {
            return m_nativeByteOrder;
        }

        /**
         * Store a value in the buffer and advance the seek position.
         * @param val value to put.
         * @return True on success, else false.
         */
        bool put8(uint8_t val);

        /**
         * Store a value in the buffer and advance the seek position.
         * @param val value to put.
         * @return True on success, else false.
         */
        bool put16(uint16_t val);

        /**
         * Store a value in the buffer and advance the seek position.
         * @param val value to put.
         * @return True on success, else false.
         */
        bool put32(uint32_t val);

        /**
         * Store a value in the buffer and advance the seek position.
         * @param val value to put.
         * @return True on success, else false.
         */
        bool put64(uint64_t val);

        /**
         * Retreive a value in the buffer and advance the seek position.
         * @param val variable to receive the value into.
         * @return True on success, else false.
         */
        bool get8(uint8_t &val);

        /**
         * Retreive a value in the buffer and advance the seek position.
         * @param val variable to receive the value into.
         * @return True on success, else false.
         */
        bool get16(uint16_t &value);

        /**
         * Retreive a value in the buffer and advance the seek position.
         * @param val variable to receive the value into.
         * @return True on success, else false.
         */
        bool get32(uint32_t &value);

        /**
         * Retreive a value in the buffer and advance the seek position.
         * @param val variable to receive the value into.
         * @return True on success, else false.
         */
        bool get64(uint64_t &value);

      private:
        /* Disable copy and assignment constructors.
         */
        Serial_buffer(Serial_buffer const &rhs);
        Serial_buffer &operator=(Serial_buffer rhs);

        /**
         * Declare the storage buffer as a union of many different types of
         * pointers so we can easily access different data types.
         */
        union Multi_ptr_t {
            void *vptr;
            uint8_t *u8;
            uint16_t *u16;
            uint32_t *u32;
            uint64_t *u64;

            Multi_ptr_t() : vptr(NULL)
            {
            }
        };

        Multi_ptr_t m_buffer;

        bool m_valid;
        const unsigned int m_maxsize;
        unsigned int m_pos;
        unsigned int m_blen;

        ByteOrder m_nativeByteOrder;
        ByteOrder m_byteOrder;
    };

} // namespace

#endif // __UTIL_SERIAL_BUFFER_H__
