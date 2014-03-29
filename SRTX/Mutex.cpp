#include "Mutex.h"
#include "base/XPRINTF.h"

namespace SRTX
{

    struct Mutex_impl
    {
        pthread_mutexattr_t attr;
        pthread_mutex_t mutex;

        ~Mutex_impl()
        {
            pthread_mutex_destroy(&mutex);
            pthread_mutexattr_destroy(&attr);
        }
    };


    Mutex::Mutex()
        : m_impl(new Mutex_impl),
        m_valid(false)
    {
        if(NULL == m_impl)
        {
            return;
        }

        m_valid = (0 == pthread_mutexattr_init(&(m_impl->attr)));
        if(!m_valid)
        {
            return;
        }

        m_valid = (0 == pthread_mutex_init(&(m_impl->mutex), &(m_impl->attr)));
    }


    bool Mutex::lock()
    {
        if(false == m_valid)
        {
            return false;
        }

        DPRINTF("Requesting mutex\n");
        return 0 == pthread_mutex_lock(&(m_impl->mutex));
    }


    bool Mutex::unlock()
    {
        if(false == m_valid)
        {
            return false;
        }

        DPRINTF("Releasing mutex\n");
        return 0 == pthread_mutex_unlock(&(m_impl->mutex));
    }


    mutex_t* Mutex::get_mutex()
    {
        return &(m_impl->mutex);
    }


    Mutex::~Mutex()
    {
        m_valid = false;

        delete m_impl;
    }

} // namespace
