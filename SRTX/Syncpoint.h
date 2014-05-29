#ifndef __SRTX_SYNCPOINT_H__
#define __SRTX_SYNCPOINT_H__

#include "SRTX/Mutex.h"
#include "units/Nanoseconds.h"

namespace SRTX
{

    /**
     * Forward declare the implementation of the mutex (PIMPL pattern).
     */
    struct Syncpoint_impl;


    class Syncpoint : public Mutex
    {

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
            bool wait(const units::Nanoseconds& timeout =
                    units::Nanoseconds(0));

            /**
             * Release threads blocked on this condition.
             * @return True on success or false on failure.
             * @note It is recommended that the associated mutex be locked
             * during this call to ensure deterministic behavior.
             */
            bool release();

            /**
             * Destructor.
             */
            virtual ~Syncpoint();

        private:

            /**
             * Pointer to the specific implementation of the Syncpoint.
             * (PIMPL pattern).
             */
            Syncpoint_impl* m_impl;

            /**
             * Boolean indicating if the mutex was successfully constructed.
             */
            bool m_valid;

    };

} // namespace

#endif // __SRTX_SYNCPOINT_H__
