#ifndef __SRTX_PUBLICATION_H__
#define __SRTX_PUBLICATION_H__

#include "base/types.h"
#include "base/XPRINTF.h"
#include "SRTX/Data_router.h"
#include "SRTX/Message.h"
#include "SRTX/Symbol_db.h"
#include "SRTX/RTC.h"

namespace SRTX {
    /**
     * This class represents the publication of some type of data in the
     * pub/sub system.
     * @param T The type of data carried by the message.
     */
    template <typename T> class Publication : public Message<T> {

        /* Alias the typename for the symbol table for messages.
         */
        typedef Symbol_db<Message<T> > db_t;

      public:
        /**
         * Constructor.
         * @param name Name of the publication.
         * @param period Periodic rate at which the message will be produced.
         */
        explicit Publication(const char *name, const units::Nanoseconds period =
                                                   units::Nanoseconds(0))
            : m_valid(false)
            , m_symbol(NULL)
        {
            static db_t &msg_db = db_t::get_instance();
            char sym_name[SYM_ENTRY_STRLEN + 1];
            snprintf(sym_name, SYM_ENTRY_STRLEN, "%s%" PRId64, name,
                     (int64_t)period);

            /* See if the periodic symbol and alias are in the database. If
             * not, create the entities that don't exist and map the symbol
             * table entry to the alias.
             */
            m_symbol = msg_db.lookup_symbol(sym_name);
            Symbol<Message<T> > *alias = msg_db.lookup_symbol(name);
            if(NULL == m_symbol) {
                DPRINTF("Creating symbol for message %s\n", sym_name);
                m_symbol = msg_db.add_symbol(sym_name);
                if((NULL == m_symbol) || (false == m_symbol->is_valid())) {
                    EPRINTF("Symbol creation failed\n");
                    delete m_symbol;
                    m_symbol = NULL;
                    return;
                }
            }
            if(NULL == alias) {
                DPRINTF("Creating alias %s\n", name);
                alias = msg_db.alias_symbol(name, m_symbol);
                if((NULL == alias) || (false == alias->is_valid())) {
                    EPRINTF("Alias creation failed\n");
                    delete m_symbol;
                    m_symbol = NULL;
                    return;
                }
            }

            /* Populate both sides of the symbol double buffer with the period.
             */
            this->m_publication_period = period;
            alias->entry->write(*this, false);
            this->m_publication_period = period;

            /* Adopt matching orphan subscriptions.
             */
            Data_router &router = Data_router::get_instance();
            router.adopt_orphans(name, *alias->entry, sizeof(Message<T>),
                                 period);

            m_valid = true;
        }

        /**
         * Is the publication valid?
         * @return True if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

        /**
         * Publish the data.
         */
        bool put()
        {
            if(false == m_valid) {
                EPRINTF(
                    "Attempting to put data to an invalid publication: %s\n",
                    m_symbol->get_name());
                return false;
            }

            /* The C++ standard does not specify how data is arranged in memory
             * among derived and inherited classes but as a practical mattter,
             * all known compilers store the base class data members first
             * followed by the data members of the derived class and we are
             * exploiting that fact when we copy a message.
             */
            return get_time(this->m_time_of_publication) &&
                   m_symbol->entry->write(*this);
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Publication(const Publication &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Publication &operator=(const Publication &);

        /**
         * Flag indicating if the publication was validly constructed.
         */
        bool m_valid;

        /**
         * A pointer to the symbol for the message transport mechanism in
         * the message database.
         */
        Symbol<Message<T> > *m_symbol;
    };

} // namespace

#endif // __SRTX_PUBLICATION_H__
