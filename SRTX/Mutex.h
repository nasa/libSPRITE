#ifndef __SRTX_MUTEX_H__
#define __SRTX_MUTEX_H__

#include "base/types.h"
#include "SRTX/Scheduler_types.h"

namespace SRTX {

    /**
     * Forward declare the implementation of the mutex (PIMPL pattern).
     */
    struct Mutex_impl;

    class Mutex {

      public:
        /**
         * Constructor.
         */
        Mutex();

        /**
         * Is the class in a valid state?
         * @return true if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

        /**
         * Grab the mutex.
         * @return true on sucess or false on failure.
         */
        bool lock();

        /**
         * Release the mutex.
         * @return true on sucess or false on failure.
         */
        bool unlock();

        /**
         * Destructor.
         */
        virtual ~Mutex();

      protected:
        /**
         * Get a pointer to the raw implementation for use by other
         * low-level classes.
         * @return Pointer to the OS native mutex type.
         */
        mutex_t *get_mutex();

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Mutex(const Mutex &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Mutex &operator=(const Mutex &);

        /**
         * Pointer to the specific implementation of the mutex.
         * (PIMPL pattern).
         */
        Mutex_impl *m_impl;

        /**
         * Boolean indicating if the mutex was successfully constructed.
         */
        bool m_valid;
    };

} // namespace

#endif // __SRTX_MUTEX_H__
