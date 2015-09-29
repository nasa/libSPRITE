#include <stdlib.h>
#include <string.h>
#include "SRTX/Base_double_buffer.h"
#include "base/XPRINTF.h"

namespace SRTX {

    Base_double_buffer::Base_double_buffer(unsigned int nbytes)
        : Buffer(nbytes)
        , m_selected(0)
    {
        m_buffer[0] = malloc(2 * nbytes);
        m_buffer[1] = static_cast<uint8_t *>(m_buffer[0]) + nbytes;

        m_valid = m_sync.is_valid() && (m_buffer[0] != NULL);
    }

    bool Base_double_buffer::read(void *data, unsigned int nbytes)
    {
        /* If the object is valid then we kwow the buffers are not NULL.
        */
        if((false == m_valid) || (nbytes > m_nbytes)) {
            return false;
        }

        if(false == m_sync.lock()) {
            EPRINTF("Failed to get mutex\n");
            return false;
        }

        memcpy(data, m_buffer[m_selected], nbytes);

        if(false == m_sync.unlock()) {
            EPRINTF("Failed to release mutex\n");
        }

        return true;
    }

    bool Base_double_buffer::read_blocking(void *data, unsigned int nbytes,
                                           const units::Nanoseconds &timeout)
    {
        /* If the object is valid then we kwow the buffers are not NULL.
        */
        if((false == m_valid) || (nbytes > m_nbytes)) {
            return false;
        }

        if(false == m_sync.lock()) {
            EPRINTF("Failed to lock mutex\n");
            return false;
        }

        if(false == m_sync.wait(timeout)) {
            m_sync.unlock();
            return false;
        }
        m_sync.condition_cleared();

        memcpy(data, m_buffer[m_selected], nbytes);

        if(false == m_sync.unlock()) {
            EPRINTF("Failed to release mutex\n");
        }

        return true;
    }

    bool Base_double_buffer::write(void const *data, unsigned int nbytes,
                                   bool signal)
    {
        /* If the object is valid then we kwow the buffers are not NULL.
        */
        if((false == m_valid) || (nbytes > m_nbytes)) {
            return false;
        }

        /* Copy data to the buffer that is not selected.
        */
        if(false == m_sync.lock()) {
            EPRINTF("Failed to obtain lock\n");
            return false;
        }

        unsigned int other_buffer = ++m_selected % 2;
        memcpy(m_buffer[other_buffer], data, nbytes);

        /* Swap the buffers.
        */
        m_selected = other_buffer;
        ++m_update_count;

        /* Signal blocked processes that an update to the buffer has
         * occured and unlock the syncpoint so they can proceed.
         */
        if(signal) {
            m_sync.condition_satisfied();
            m_sync.release();
        }

        if(false == m_sync.unlock()) {
            EPRINTF("Failed to release lock\n");
        }

        return true;
    }

    Base_double_buffer::~Base_double_buffer()
    {
        m_valid = false;
        free(m_buffer[0]);
    }

    bool copy(Base_double_buffer &dest, Base_double_buffer &src,
              unsigned int nbytes)
    {

        uint8_t tmp[nbytes];
        if(false == src.read(tmp, nbytes)) {
            return false;
        }

        return dest.write(tmp, nbytes);
    }

} // namespace
