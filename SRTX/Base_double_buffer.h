#ifndef __SRTX_BASE_DOUBLE_BUFFER_H__
#define __SRTX_BASE_DOUBLE_BUFFER_H__

#include "SRTX/Buffer.h"

namespace SRTX {

    /**
     * An untyped double buffer.
     */
    class Base_double_buffer : public Buffer {
      public:
        /**
         * Constructor.
         * @param nbytes Single buffer size in number of bytes.
         */
        explicit Base_double_buffer(unsigned int nbytes);

        /**
         * Read from the buffer.
         * @param data Pointer to data buffer to read into.
         * @param nbytes Buffer size in bytes.
         * @return True on success or false on failure.
         */
        bool read(void *data, unsigned int nbytes);

        /**
         * Wait for an update to the buffer and return the new value.
         * @param data Pointer to data buffer to read into.
         * @param nbytes Buffer size in bytes.
         * @param timeout Absolute time at which to timeout
         * Default behavior (timeout=0) is to wait forever.
         * @return True on success or false on failure.
         */
        bool read_blocking(void *data, unsigned int nbytes,
                           const units::Nanoseconds &timeout =
                               units::Nanoseconds(0));

        /**
         * Write to the buffer.
         * When the write operation has completed, the buffers will swap.
         * @param data Data to be written.
         * @param nbytes Buffer size in bytes.
         * @param signal Indicate whether to signal blocked readers.
         * @return True on success or false on failure.
         */
        bool write(void const *data, unsigned int nbytes, bool signal = true);

        /**
         * Destructor.
         */
        virtual ~Base_double_buffer();

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Base_double_buffer(const Base_double_buffer &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Base_double_buffer &operator=(const Base_double_buffer &);

        /**
         * Selector that indicates which buffer is active.
         */
        unsigned int m_selected;

        /**
         * Pointers to the buffers.
         */
        void *m_buffer[2];
    };

    bool copy(Base_double_buffer &dest, Base_double_buffer &src,
              unsigned int nbytes);

} // namespace

#endif // __SRTX_BASE_DOUBLE_BUFFER_H__
