/******************************************************************************
 * Copyright (c) 2012 - Daniel L. Heater
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#ifndef __SRTX_BUFFER_H__
#define __SRTX_BUFFER_H__

#include "SRTX/Syncpoint.h"


namespace SRTX
{

    /**
     * An untyped data buffer.
     */
    class Buffer
    {
        public:

            /**
             * Constructor.
             * @param nbytes Buffer entry size in number of bytes.
             */
            explicit Buffer(unsigned int nbytes);

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
            virtual bool read(void* data, unsigned int nbytes) = 0;

            /**
             * Wait for an update to the buffer and return the new value.
             * @param data Pointer to data buffer to read into.
             * @param nbytes Buffer size in bytes.
             * @param timeout Absolute time at which to timeout
             * Default behavior (timeout=0) is to wait forever.
             * @return True on success or false on failure.
             */
            virtual bool read_blocking(void* data, unsigned int nbytes,
                    const units::Nanoseconds& timeout = units::Nanoseconds(0))
                = 0;

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
             * @param signal Inidate whether blocked readers should be signaled.
             * @return True on success or false on failure.
             */
            virtual bool write(void const* data, unsigned int nbytes,
                    bool signal = true) = 0;

            /**
             * This count indicates the number of times the buffer has been
             * updated.
             * @return Number of times the buffer has been written to.
             * @warning This counter is subject to rollover.
             */
            unsigned int get_update_count() const
            {
                return m_update_count;
            }

        protected:

            /**
             * Number of bytes of data stored in a buffer.
             */
            unsigned int m_nbytes;

            /**
             * Selector that indicates which buffer is active.
             */
            unsigned int m_selected;

            /**
             * State variable that indicates whether the class was validily
             * constructed.
             */
            bool m_valid;

            /**
             * Token used to synchronize access to the buffer and to signal
             * threads that are waiting on an update to the buffer.
             */
            Syncpoint m_sync;

            /**
             * Indicates if a blocking read call was forcibly aborted.
             */
            bool m_read_abort;

            /**
             * Count of the number of time this buffer has been updated.
             */
            unsigned int m_update_count;
    };


    /**
     * Define a custom copy operation that reads data for a source buffer
     * and writes it into a desination buffer.
     * @param dest Destination buffer.
     * @param src Source buffer.
     * @param nbytes Number of bytes to copy.
     * @return True of success and false on failure.
     */
    bool copy_entry(Buffer& dest, Buffer& src, unsigned int nbytes);

} // namespace

#endif // __SRTX_BUFFER_H__
