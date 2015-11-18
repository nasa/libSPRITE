#include <stdlib.h>
#include <string.h>
#include "SRTX/Base_ring_buffer.h"
#include "base/XPRINTF.h"

namespace SRTX {

    Base_ring_buffer::Base_ring_buffer(unsigned int nbytes, unsigned int nelem)
        : Buffer(nbytes)
        , m_nelems(nelem)
        , m_free(nelem)
        , m_size(nbytes * nelem)
        , m_buffer(static_cast<char *>(malloc(m_size)))
        , m_head(m_buffer)
        , m_tail(m_buffer)
    {
        m_valid = m_sync.is_valid() && (m_buffer != NULL);
    }

    bool Base_ring_buffer::_read(void *data, unsigned int nbytes)
    {
        memcpy(data, m_tail, nbytes);
        ++m_free;

        /* Move the tail pointer
        */
        m_tail += m_nbytes;
        if(m_tail >= (m_buffer + m_size)) {
            m_tail -= m_size;
        }

        m_sync.unlock();

        return true;
    }

    bool Base_ring_buffer::read(void *data, unsigned int nbytes)
    {
        /* If the object is valid then we kwow the buffer is not NULL.
         */
        if((false == m_valid) || (nbytes > m_nbytes)) {
            return false;
        }

        m_sync.lock();

        /* Is there anything to be read?
         */
        if(m_free == m_nelems) {
            m_sync.unlock();
            return false;
        }

        return this->_read(data, nbytes);
    }

    bool Base_ring_buffer::read_blocking(void *data, unsigned int nbytes,
                                         const units::Nanoseconds &timeout)
    {
        /* If the object is valid then we kwow the buffer is not NULL.
         */
        if((false == m_valid) || (nbytes > m_nbytes)) {
            return false;
        }

        m_sync.lock();

        /* If the buffer is empty, wait for data or timeout.
         */
        if(m_free == m_nelems) {
            if((false == m_sync.wait(timeout)) || (m_free == m_nelems)) {
                m_sync.unlock();
                return false;
            }
        }
        m_sync.condition_cleared();

        return this->_read(data, nbytes);
    }

    bool Base_ring_buffer::write(void const *data, unsigned int nbytes,
                                 bool signal)
    {
        /* If the object is valid then we kwow the buffer is not NULL.
        */
        if((false == m_valid) || (nbytes > m_nbytes)) {
            return false;
        }

        m_sync.lock();

        /* Is there room to add an item to the queue?
        */
        if(m_free <= 0) {
            m_sync.unlock();
            return false;
        }

        /* Copy data to the buffer.
        */
        memcpy(m_head, data, nbytes);
        --m_free;

        /* Move the head pointer.
        */
        m_head += m_nbytes;
        if(m_head >= (m_buffer + m_size)) {
            m_head -= m_size;
        }

        /* Signal blocked processes that an update to the buffer has
         * occured and unlock the syncpoint so they can proceed.
         */
        if(true == signal) {
            m_sync.condition_satisfied();
            m_sync.release();
        }

        m_sync.unlock();

        return true;
    }

    Base_ring_buffer::~Base_ring_buffer()
    {
        m_valid = false;
        free(m_buffer);
    }

} // namespace
