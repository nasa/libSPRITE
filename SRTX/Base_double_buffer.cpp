#include <stdlib.h>
#include <string.h>
#include "Base_double_buffer.h"


namespace SRTX
{

    Base_double_buffer::Base_double_buffer(unsigned int nbytes) :
        m_nbytes(nbytes),
        m_selected(0),
        m_read_abort(false),
        m_update_count(0)
    {
        m_buffer[0] = malloc(2 * nbytes);
        m_buffer[1] = static_cast<uint8_t*>(m_buffer[0]) + nbytes;

        m_valid = m_sync.is_valid() && (m_buffer[0] != NULL);
    }


    bool Base_double_buffer::read(void* data, unsigned int nbytes)
    {
        /* If the object is valid then we kwow the buffers are not NULL.
         */
        if((false == m_valid) || (nbytes > m_nbytes))
        {
            return false;
        }

        m_sync.lock();
        memcpy(data, m_buffer[m_selected], nbytes);
        m_sync.unlock();

        return true;
    }


    bool Base_double_buffer::read_blocking(void* data, unsigned int nbytes,
            const units::Nanoseconds& timeout)
    {
        /* If the object is valid then we kwow the buffers are not NULL.
         */
        if((false == m_valid) || (nbytes > m_nbytes))
        {
            return false;
        }

        m_sync.lock();
        m_read_abort = false;
        if(false == m_sync.wait(timeout) || m_read_abort)
        {
            m_sync.unlock();
            return false;
        }

        memcpy(data, m_buffer[m_selected], nbytes);
        m_sync.unlock();

        return true;
    }


    void Base_double_buffer::abort_read()
    {
        m_sync.lock();
        m_read_abort = true;
        m_sync.release();
        m_sync.unlock();
    }


    bool Base_double_buffer::write(void const* data, unsigned int nbytes)
    {
        /* If the object is valid then we kwow the buffers are not NULL.
         */
        if((false == m_valid) || (nbytes > m_nbytes))
        {
            return false;
        }

        /* Copy data to the buffer that is not selected.
         */
        m_sync.lock();
        unsigned int other_buffer = ++m_selected % 2;
        memcpy(m_buffer[other_buffer], data, nbytes);

        /* Swap the buffers.
         */
        m_selected = other_buffer;
        ++m_update_count;

        /* Signal blocked processes that an update to the buffer has
         * occured and unlock the syncpoint so they can proceed.
         */
        m_sync.release();
        m_sync.unlock();

        return true;
    }


    Base_double_buffer::~Base_double_buffer()
    {
        m_valid = false;
        free(m_buffer[0]);
    }


    bool copy(Base_double_buffer& dest, Base_double_buffer& src,
            unsigned int nbytes)
    {
        uint8_t tmp[nbytes];

        if(false == src.read(tmp, nbytes))
        {
            return false;
        }

        return dest.write(tmp, nbytes);
    }

} // namespace
