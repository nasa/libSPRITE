#ifndef __SRTX_MESSAGE_DB_H__
#define __SRTX_MESSAGE_DB_H__

#include "SRTX/Symbol_table.h"
#include "SRTX/Message.h"

namespace SRTX {
    template <typename T, template <typename> class msg_t>
    class Message_db : public Symbol_table<msg_t<T> > {
      public:
        /**
         * Get an instance to the message database.
         * The message database is created as a singleton.
         * @return A reference to the message database.
         */
        static Message_db &get_instance()
        {
            static Message_db instance;

            return instance;
        }

      private:
        /**
         * Constructor.
         * The constructor is made private as part of the singleton pattern.
         */
        Message_db()
        {
        }

        /**
         * Copy constructor.
         * The copy constructor is made private as part of the singleton
         * pattern.
         */
        Message_db(const Message_db &);

        /**
         * Assignment operator.
         * The assignment operator is made private as part of the singleton
         * pattern.
         */
        Message_db &operator=(const Message_db &);
    };

} // namespace

#endif // __SRTX_MESSAGE_DB_H__
