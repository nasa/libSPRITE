#ifndef __SRTX_BASE_RING_BUFFER_H__
#define __SRTX_BASE_RING_BUFFER_H__

#include "SRTX/Buffer.h"

namespace SRTX
{

    /**
     * An untyped ring buffer.
     */
    class Base_ring_buffer: public Buffer
    {
        public:

            /**
             * Constructor.
             * @param nbytes Single buffer size in number of bytes.
             * @param nelem Number of elememnts that can be stored in the
             * buffer.
             */
            explicit Base_ring_buffer(unsigned int nbytes, unsigned int nelem);

            /**
             * Read from the buffer.
             * @param data Pointer to data buffer to read into.
             * @param nbytes Buffer size in bytes.
             * @return True on success or false on failure.
             */
            bool read(void* data, unsigned int nbytes);

            /**
             * Wait for an update to the buffer and return the new value.
             * @param data Pointer to data buffer to read into.
             * @param nbytes Buffer size in bytes.
             * @param timeout Absolute time at which to timeout
             * Default behavior (timeout=0) is to wait forever.
             * @return True on success or false on failure.
             */
            bool read_blocking(void* data, unsigned int nbytes,
                    const units::Nanoseconds& timeout = units::Nanoseconds(0));

            /**
             * Write to the buffer.
             * When the write operation has completed, the buffers will swap.
             * @param data Data to be written.
             * @param nbytes Buffer size in bytes.
             * @param signal Indicate whether blocked readers should be signaled.
             * @return True on success or false on failure.
             */
            bool write(void const* data, unsigned int nbytes, bool signal = true);

            /**
             * Test if the ring buffer is empty.
             * @return true if empty, else false.
             */
            bool is_empty() const
            {
                return m_free == m_nelems;
            }

            /**
             * Test if the ring buffer is full.
             * @return true if full, else false.
             */
            bool is_full() const
            {
                return 0 == m_free;
            }

            /**
             * Read how many elements are populated.
             * @return The number of elements in use.
             */
            unsigned int nelems_used() const
            {
                return m_nelems - m_free;
            }

            /**
             * Read how many elements are free.
             * @return The number of elements available.
             */
            unsigned int nelems_free() const
            {
                return m_free;
            }

            /**
             * Destructor.
             */
            virtual ~Base_ring_buffer();

        private:

            /**
             * Number of buffer elements that can be stored.
             */
            unsigned int m_nelems;

            /**
             * Number of free elements in the buffer.
             */
            unsigned int m_free;

            /**
             * Pointer to the buffer.
             */
            char* m_buffer;

            /**
             * Buffer head.
             */
            char* m_head;

            /**
             * Buffer tail.
             */
            char* m_tail;

            /**
             * Buffer size.
             */
            const unsigned int m_size;

            /**
             * Internal function to read from the buffer.
             * @param data Pointer to data buffer to read into.
             * @param nbytes Buffer size in bytes.
             * @return True on success or false on failure.
             */
            bool _read(void* data, unsigned int nbytes);
    };

} // namespace

#endif // __SRTX_BASE_RING_BUFFER_H__
