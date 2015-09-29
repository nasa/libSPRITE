#include <errno.h>
#include <pthread.h>
#include <time.h>
#include "SRTX/Syncpoint.h"
#include "base/XPRINTF.h"

namespace SRTX {

    struct Syncpoint_impl {
        bool is_valid;

        pthread_cond_t cond;
        pthread_condattr_t attr;

        Syncpoint_impl()
            : is_valid(false)
            , cond()
            , attr()
        {
            int rval = pthread_cond_init(&cond, NULL);
            if(rval) {
                PERRORNO(rval, "pthread_cond_init");
                return;
            }

/* This code block was written to try to take advantage of the
 * monotonic clock, but the pthread_condattr_setclock call is
 * absent in Cygwin and RTEMS.
 * TODO Use the monotonic clock when it is available and submit a
 * patch to RTEMS to support pthread_condattr_setclock.
 */
#if defined _POSIX_MONOTONIC_CLOCK &&_POSIX_CLOCK_SELECTION

            /* Initialize the condition variable attributes.
            */
            pthread_condattr_t attr;
            rval = pthread_condattr_init(&attr);
            if(rval) {
                PERRORNO(rval, "pthread_condattr_init");
                return;
            }

            /* Set the condition variable attributes to use the monotonic
             * clock.
             */
            rval = pthread_condatttr_setclock(&attr, CLOCK_MONOTONIC);
            if(rval) {
                PERRORNO(rval, "pthread_condattr_setclock");
                return;
            }

            /* Initialize the condition variable.
            */
            rval = pthread_cond_init(&cond, &attr);
            if(rval) {
                PERRORNO(rval, "pthread_cond_init");
                return;
            }
#else
#warning MONOTONIC CLOCK SUPPORT IS NOT AVAILABLE - This is not fatal.
#endif

            is_valid = true;
        }

        ~Syncpoint_impl()
        {
            pthread_cond_destroy(&cond);
            pthread_condattr_destroy(&attr);
        }
    };

    Syncpoint::Syncpoint()
        : m_impl(new Syncpoint_impl)
        , m_valid(false)
        , m_wait_condition(false)
        , m_abort(false)
    {
        if(NULL == m_impl) {
            return;
        }

        m_valid = m_impl->is_valid;
    }

    Syncpoint::~Syncpoint()
    {
        m_valid = false;
        delete m_impl;
    }

    bool Syncpoint::wait(const units::Nanoseconds &timeout)
    {
        /* If timeout is 0, wait forever.
        */
        int rval = 0;
        m_abort = false;
        if(0 == timeout) {
            while((false == m_wait_condition) && (false == m_abort)) {
                rval = pthread_cond_wait(&(m_impl->cond), get_mutex());
                if(rval) {
                    PERRORNO(rval, "pthread_cond_wait");
                    return false;
                }
            }
        } else {
            DPRINTF("Timeout(nsec) = %lld\n", int64_t(timeout));

            struct timespec ts;
            ts.tv_sec = timeout / units::SEC;
            ts.tv_nsec = timeout % units::SEC;

            DPRINTF("Timeout = %d.%ld\n", (int)ts.tv_sec, ts.tv_nsec);
            while((false == m_wait_condition) && (rval != ETIMEDOUT) &&
                  (false == m_abort)) {
                rval =
                    pthread_cond_timedwait(&(m_impl->cond), get_mutex(), &ts);
                if(rval && (rval != ETIMEDOUT)) {
                    PERRORNO(rval, "pthread_cond_timeout");
                    return false;
                }
            }
        }

        return !m_abort;
    }

    bool Syncpoint::inverse_wait()
    {
        while(true == m_wait_condition) {
            int rval = pthread_cond_wait(&(m_impl->cond), get_mutex());
            if(rval) {
                PERRORNO(rval, "pthread_cond_wait");
                return false;
            }
        }

        return true;
    }

    bool Syncpoint::release()
    {
        int rval = pthread_cond_broadcast(&(m_impl->cond));
        if(rval) {
            PERRORNO(rval, "pthread_cond_broadcast");
            return false;
        }

        return true;
    }

} // namespace
