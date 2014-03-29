#ifndef __SRTX_BASE_DOUBLE_BUFFER_H__
#define __SRTX_BASE_DOUBLE_BUFFER_H__

#include "Syncpoint.h"


namespace SRTX
{

    /**
     * An untyped data buffer.
     */
    class Base_double_buffer
    {
        public:

            /**
             * Constructor.
             * @param nbytes Single buffer size in number of bytes.
             */
            explicit Base_double_buffer(unsigned int nbytes);

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
             * This count indicates the number of times the buffer has been updated.
             * @return Number of times the buffer has been written to.
             * @warning This counter is subject to rollover.
             */
            unsigned int get_update_count() const
            {
                return m_update_count;
            }

            /**
             * Destructor.
             */
            virtual ~Base_double_buffer();

        private:

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
             * Count of the number of time this buffer has been updated.
             */
            unsigned int m_update_count;

            /**
             * Pointers to the buffers.
             */
            void* m_buffer[2];
    };


    /**
     * Define a custom copy operation that moves reads data for a source buffer
     * and writes it into a desination buffer.
     * @param dest Destination buffer.
     * @param src Source buffer.
     * @param nbytes Number of bytes to copy.
     * @return True of success and false on failure.
     */
    bool copy(Base_double_buffer& dest, Base_double_buffer& src,
            unsigned int nbytes);

} // namespace

#endif // __SRTX_BASE_DOUBLE_BUFFER_H__
