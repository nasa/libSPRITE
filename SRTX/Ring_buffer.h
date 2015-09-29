#ifndef __SRTX_RING_BUFFER_H__
#define __SRTX_RING_BUFFER_H__

#include "SRTX/Base_ring_buffer.h"

namespace SRTX {

    template <typename T> class Ring_buffer : public Base_ring_buffer {

      public:
        /**
         * Constructor.
         * @param nelem Number of elememnts that can be stored in the
         * buffer.
         */
        Ring_buffer(unsigned int nelem) : Base_ring_buffer(sizeof(T), nelem)
        {
        }

        /**
         * Read from the buffer.
         * @param data Reference to data buffer to read into.
         * @return True on success or false on failure.
         */
        bool read(T &data)
        {
            return Base_ring_buffer::read(&data, sizeof(T));
        }

        /**
         * Wait for new data to be queued and read the new value.
         * @param data Reference to data buffer to read into.
         * @param timeout Absolute time at which to timeout
         * Default behavior (timeout=0) is to wait forever.
         * @return True on success or false on failure.
         */
        bool read_blocking(T &data, const units::Nanoseconds &timeout =
                                        units::Nanoseconds(0))
        {
            return Base_ring_buffer::read_blocking(&data, sizeof(T), timeout);
        }

        /**
         * Force all pending read blocking calls to be released immediately.
         * This function is used to cause a read blocking call to be
         * aborted. The read blocking call should return indicating that an
         * error occurred.
         */
        void abort_read()
        {
            Base_ring_buffer::abort_read();
        }

        /**
         * Write to the buffer.
         * @param data Data to be written.
         * @param signal Indicate whether blocked readers should be signaled.
         * @return True on success or false on failure.
         */
        bool write(const T &data, bool signal = true)
        {
            return Base_ring_buffer::write(&data, sizeof(T), signal);
        }
    };

} // namespace

#endif // __SRTX_RING_BUFFER_H__
