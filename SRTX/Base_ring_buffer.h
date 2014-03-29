#ifndef __SRTX_BASE_RING_BUFFER_H__
#define __SRTX_BASE_RING_BUFFER_H__

#include "Syncpoint.h"

namespace SRTX
{

    /**
     * An untyped data buffer.
     */
    class Base_ring_buffer
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
             * Is the class in a valid state.
             * The class will not be valid if it did not construct properly or
             * is in the process of being deleted.
             * @return True if valid, else false.
             */
            bool is_valid() const
            {
                return m_valid;
            }

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
             * Force all pending read blocking calls to be released immediately.
             * This function is used to cause a read blocking call to be
             * aborted. The read blocking call should return indicating that an
             * error occurred.
             */
            void abort_read();

            /**
             * Write to the buffer.
             * When the write operation has completed, the buffers will swap.
             * @param data Data to be written.
             * @param nbytes Buffer size in bytes.
             * @return True on success or false on failure.
             */
            bool write(void const* data, unsigned int nbytes);

            /**
             * Destructor.
             */
            virtual ~Base_ring_buffer();

        private:

            /**
             * Number of bytes of data stored in a buffer element.
             */
            unsigned int m_nbytes;

            /**
             * Number of buffer elements that can be stored.
             */
            unsigned int m_nelems;

            /**
             * Number of free elements in the buffer.
             */
            unsigned int m_free;

            /**
             * State variable that indicates whether the class was validily
             * constructed.
             */
            bool m_valid;

            /**
             * Token used to synchronize access to signal threads that are
             * waiting on an update to the buffer.
             * @note The double buffer does not need the syncpoint to ensure
             * data atomicity. Instead it is used for more sophisticated usage
             * patterns such as signaling buffer updates.
             */
            Syncpoint m_sync;

            /**
             * Indicates if a blocking read call was forcibly aborted.
             */
            bool m_read_abort;

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
