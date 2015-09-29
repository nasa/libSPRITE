#ifndef __SRTX_DATA_ROUTER_H__
#define __SRTX_DATA_ROUTER_H__

#include "units/Nanoseconds.h"
#include "SRTX/Base_double_buffer.h"

namespace SRTX {

    /**
     * Forward declare the implementation details of a process (PIMPL pattern).
     */
    struct Data_router_impl;

    class Data_router {
      public:
        /**
         * Get an instance to the symbol database.
         * The symbol database is created as a singleton.
         * @return A reference to the symbol database.
         */
        static Data_router &get_instance()
        {
            static Data_router instance;

            return instance;
        }

        /**
         * Register a request to copy data periodically
         * @param source Source buffer.
         * @param dest Destination buffer.
         * @param nbytes Number of bytes to transfer.
         * @param period Period at which the transfer should occur.
         * @return true on success or false on failure.
         */
        bool register_transfer(Base_double_buffer &source,
                               Base_double_buffer &dest, unsigned int nbytes,
                               units::Nanoseconds period);

        /**
         * Store the parameters of a subscribe attempt that was made when
         * no publisher was present as an orphan.  When the subscriber runs
         * before the publisher, the subscription process cannot complete
         * so we store the parameters for that attempt off as an orphan to
         * be adopted later.
         * @param name Message name.
         * @param period Subscription period.
         */
        void register_orphan(const char *name, units::Nanoseconds period,
                             Base_double_buffer &buffer);

        /**
         * Look for subscription attempts that were made before the
         * publisher was created and claim any matches.
         *
         * When the subscriber runs before the publisher, the subscription
         * process cannot complete so we store the parameters for that
         * attempt off as an orphan to be adopted later.
         * @param name Message name.
         * @param period Publication period.
         */
        void adopt_orphans(const char *name, Base_double_buffer &buffer,
                           unsigned int nbytes, units::Nanoseconds period);

        /**
         * Transfer data that has been scheduled through the
         * register_transfer() function to be transfered in this period.
         * This function is at the heart of multi-rate publish/subscribe.
         * This is where the data gets moved between the seperate buffers
         * allocated to each rategroup.
         * @param ref_time Reference time.
         */
        void do_transfers(const units::Nanoseconds &ref_time);

      private:
        /**
         * Constructor.
         * The constructor is made private as part of the singleton
         * pattern.
         */
        Data_router();

        /**
         * Copy constructor.
         * The copy constructor is made private as part of the singleton
         * pattern.
         */
        Data_router(const Data_router &);

        /**
         * Assignment operator.
         * The assignment operator is made private as part of the singleton
         * pattern.
         */
        Data_router &operator=(const Data_router &);

        /**
         * Destructor.
         */
        ~Data_router();

        /**
         * Internal data router stuff. (PIMPL pattern).
         */
        Data_router_impl *m_impl;
    };

} // namespace

#endif // __SRTX_DATA_ROUTER_H__
