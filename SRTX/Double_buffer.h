#ifndef __SRTX_DOUBLE_BUFFER_H__
#define __SRTX_DOUBLE_BUFFER_H__

#include "SRTX/Base_double_buffer.h"

namespace SRTX {

    template <typename T> class Double_buffer : public Base_double_buffer {

      public:
        Double_buffer() : Base_double_buffer(sizeof(T))
        {
        }

        /**
         * Read from the buffer.
         * @param data Reference to data buffer to read into.
         * @return True on success or false on failure.
         */
        bool read(T &data)
        {
            return Base_double_buffer::read(&data, sizeof(T));
        }

        /**
         * Wait for the buffer to be updated then read the new value.
         * @param data Reference to data buffer to read into.
         * @param timeout Absolute time at which to timeout
         * Default behavior (timeout=0) is to wait forever.
         * @return True on success or false on failure.
         */
        bool read_blocking(T &data, const units::Nanoseconds &timeout =
                                        units::Nanoseconds(0))
        {
            return Base_double_buffer::read_blocking(&data, sizeof(T), timeout);
        }

        /**
         * Force all pending read blocking calls to be released immediately.
         * This function is used to cause a read blocking call to be
         * aborted. The read blocking call should return indicating that an
         * error occurred.
         */
        void abort_read()
        {
            Base_double_buffer::abort_read();
        }

        /**
         * Write to the buffer. When the write operation has completed, the
         * buffers will swap.
         * @param data Data to be written.
         * @param signal Inidicate whether to signal blocked readers.
         * @return True on success or false on failure.
         */
        bool write(const T &data, bool signal = true)
        {
            return Base_double_buffer::write(&data, sizeof(T), signal);
        }
    };

} // namespace

#endif // __SRTX_DOUBLE_BUFFER_H__
