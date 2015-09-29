#ifndef __SRTX_SUBSCRIPTION_H__
#define __SRTX_SUBSCRIPTION_H__

#include "base/types.h"
#include "base/XPRINTF.h"
#include "SRTX/Data_router.h"
#include "SRTX/Message.h"
#include "SRTX/Symbol_db.h"

namespace SRTX {
    /**
     * This class represents the subscription of some type of data in the
     * pub/sub system.
     * @param T The type of data carried by the message.
     */
    template <typename T> class Subscription : public Message<T> {

        typedef Symbol_db<Message<T> > db_t;

      public:
        /**
         * Constructor.
         * @param name Name of the subscription.
         * @param period Periodic rate of the message's receiver.
         */
        explicit Subscription(const char *name,
                              const units::Nanoseconds period =
                                  units::Nanoseconds(0))
            : m_valid(false)
            , m_updated(false)
            , m_last_publication_time(-1)
            , m_symbol(NULL)
        {
            static db_t &msg_db = db_t::get_instance();

            /* See if there is already a symbol for the message in the
             * database. If there is no symbol yet, create one.
             * We append the process period (if periodic) to the symbol name to
             * create a unique symbol entry for each rategroup or the raw name
             * which is the same as the alias for aperiodic subscriptions.
             */
            char sym_name[SYM_ENTRY_STRLEN + 1];
            snprintf(sym_name, SYM_ENTRY_STRLEN, "%s%" PRId64, name,
                     int64_t(period));
            m_symbol = msg_db.lookup_symbol(sym_name);
            if(m_symbol) {
                DPRINTF("Found symbol for message %s\n", sym_name);
                m_valid = true;
                return;
            }

            DPRINTF("Creating symbol for message %s\n", sym_name);
            m_symbol = msg_db.add_symbol(sym_name);
            if((NULL == m_symbol) || (false == m_symbol->is_valid())) {
                EPRINTF("Symbol creation failed\n");
                delete m_symbol;
                m_symbol = NULL;
                return;
            }

            /* Get a reference to the data router.
             */
            Data_router &router = Data_router::get_instance();

            /* Look for the message alias (name without the period appended)
             * and register the symbol with the data router to handle data
             * routing between rategroups.
             */
            Symbol<Message<T> > *alias = msg_db.lookup_symbol(name);
            if(NULL == alias) {
                DPRINTF("%s: No alias found\n", sym_name);
                router.register_orphan(name, period, *m_symbol->entry);
            } else {
                alias->entry->read(*this);

                units::Nanoseconds pub_period = this->m_publication_period;

                units::Nanoseconds slower_period =
                    (period > pub_period) ? period : pub_period;
                DPRINTF(
                    "%s: Registering a transfer request from period = %" PRId64
                    " to period %" PRId64 "\n",
                    sym_name, int64_t(pub_period), int64_t(period));

                /* Register a request to the data router to move data from the
                 * aliased publication symbol table entry to the subscribers
                 * symbol table entry at the slower of the publisher's and
                 * subscriber's period.
                 */
                if(false == router.register_transfer(
                                *alias->entry, *m_symbol->entry,
                                sizeof(Message<T>), slower_period)) {
                    EPRINTF("Register transfer failed\n");
                    delete m_symbol;
                    m_symbol = NULL;
                    return;
                }
            }

            m_valid = true;
        }

        /**
         * Is the subscription valid?
         * @return True if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

        /**
         * Get the latest data.
         * @return True on success or false on failure.
         */
        bool get()
        {
            if(false == m_valid) {
                EPRINTF(
                    "Attempting to get data from an invalid subscription: %s\n",
                    m_symbol->get_name());
                return false;
            }

            /* The C++ standard does not specify how data is arranged in memory
             * among derived and inherited classes but as a practical mattter,
             * all known compilers store the base class data members first
             * followed by the data members of the derived class and we are
             * exploiting that fact when we copy a message.
             */
            if(false == m_symbol->entry->read(*this)) {
                m_updated = false;
                return false;
            }

            units::Nanoseconds publication_time = this->get_publication_time();
            if(-1 == publication_time) {
                m_updated = false;
                return false;
            }

            m_updated = publication_time != m_last_publication_time;
            m_last_publication_time = publication_time;

            return true;
        }

        /**
         * Block on the subscription until new data is published, then get the
         * new data.
         * @param timeout Absolute time at which to timeout
         * behavior (timeout=0) is to wait forever.
         * @return True on success or false on failure.
         */
        bool get_blocking(const units::Nanoseconds &timeout =
                              units::Nanoseconds(0))
        {
            if(false == m_valid) {
                EPRINTF(
                    "Attempting to get data from an invalid subscription: %s\n",
                    m_symbol->get_name());
                return false;
            }

            /* The C++ standard does not specify how data is arranged in memory
             * among derived and inherited classes but as a practical mattter,
             * all known compilers store the base class data members first
             * followed by the data members of the derived class and we are
             * exploiting that fact when we copy a mesassage.
             */
            if(false == m_symbol->entry->read_blocking(*this, timeout)) {
                m_updated = false;
                return false;
            }

            units::Nanoseconds publication_time = this->get_publication_time();
            if(-1 == publication_time) {
                EPRINTF("Message not published\n");
                m_updated = false;
                return false;
            }

            m_updated = publication_time != m_last_publication_time;
            m_last_publication_time = publication_time;

            return true;
        }

        /**
         * Force all pending get_value_blocking calls to be released
         * immediately.  This function is used to cause a get_value_blocking
         * call to be aborted. The get_value_blocking call should return
         * indicating that an error occurred.
         */
        void abort_get()
        {
            m_symbol->entry->abort_read();
        }

        /**
         * Was the subscription updated on the last call to get()?
         * @return True if the subscription was updated, else false.
         */
        bool was_updated() const
        {
            return m_updated;
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Subscription(const Subscription &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Subscription &operator=(const Subscription &);

        /**
         * Flag indicating if the subscription was validly constructed.
         */
        bool m_valid;

        /**
         * Flag indicating that the data was updated during the last call to
         * get().
         */
        bool m_updated;

        /**
         * Time of the last publication.
         */
        units::Nanoseconds m_last_publication_time;

        /**
         * A pointer to the symbol for the message transport mechanism in the
         * message database.
         */
        Symbol<Message<T> > *m_symbol;
    };

} // namespace

#endif // __SRTX_SUBSCRIPTION_H__
