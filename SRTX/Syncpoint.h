#ifndef __SRTX_SYNCPOINT_H__
#define __SRTX_SYNCPOINT_H__

#include "SRTX/Mutex.h"
#include "units/Nanoseconds.h"

namespace SRTX {

    /**
     * Forward declare the implementation of the mutex (PIMPL pattern).
     */
    struct Syncpoint_impl;

    class Syncpoint : public Mutex {

      public:
        /**
         * Constructor.
         */
        Syncpoint();

        /**
         * Is the class in a valid state?
         * @return true if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

        /**
         * Wait for release from the syncpoint or optionally timeout.
         * @param timeout Absolute time of timeout in nanoseconds. If
         * timeout is 0, it is ignored, and the call waits forever.
         * @return True if released or timed out. False on failure.
         * @note The associated mutex must be locked prior to calling this
         * routine and will be locked when this routine returns.
         */
        bool wait(const units::Nanoseconds &timeout = units::Nanoseconds(0));

        /**
         * Wait, but with the wait condition inverted.
         * @return True on success, false on failure.
         */
        bool inverse_wait();

        /**
         * Release threads blocked on this condition.
         * @return True on success or false on failure.
         * @note It is recommended that the associated mutex be locked
         * during this call to ensure deterministic behavior.
         */
        bool release();

        /**
         * Let the syncpoint know that the condition to release tasks
         * has been satisfied.
         */
        void condition_satisfied(void)
        {
            m_wait_condition = true;
        }

        /**
         * Abort the wait even though the condition is not satisified.
         */
        void abort_wait(void)
        {
            m_abort = true;
            release();
        }

        /**
         * Let the syncpoint know that the condition to release tasks
         * is no longer satisfied.
         */
        void condition_cleared(void)
        {
            m_wait_condition = false;
        }

        /**
         * Destructor.
         */
        virtual ~Syncpoint();

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Syncpoint(const Syncpoint &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Syncpoint &operator=(const Syncpoint &);

        /**
         * Pointer to the specific implementation of the Syncpoint.
         * (PIMPL pattern).
         */
        Syncpoint_impl *m_impl;

        /**
         * Boolean indicating if the mutex was successfully constructed.
         */
        bool m_valid;

        /**
         * Condition used to indicate whether the wait criteria has been
         * satisfied.
         */
        bool m_wait_condition;

        /**
         * Flag to indicate that we want to abort the wait even tough the
         * condition has not been satisfied.
         */
        bool m_abort;
    };

} // namespace

#endif // __SRTX_SYNCPOINT_H__
