#ifndef __SRTX_SYMBOL_DB_H__
#define __SRTX_SYMBOL_DB_H__

#include "SRTX/Symbol_table.h"

namespace SRTX {
    template <typename T> class Symbol_db : public Symbol_table<T> {
      public:
        /**
         * Define a type alias (shorthand) for the type of data stored in
         * the database.
         */
        typedef T value_t;

        /**
         * Get an instance to the symbol database.
         * The symbol database is created as a singleton.
         * @return A reference to the symbol database.
         */
        static Symbol_db &get_instance()
        {
            static Symbol_db instance;

            return instance;
        }

      private:
        /**
         * Constructor.
         * The constructor is made private as part of the singleton
         * pattern.
         */
        Symbol_db()
        {
        }

        /**
         * Copy constructor.
         * The copy constructor is made private as part of the singleton
         * pattern.
         */
        Symbol_db(const Symbol_db &);

        /**
         * Assignment operator.
         * The assignment operator is made private as part of the singleton
         * pattern.
         */
        Symbol_db &operator=(const Symbol_db &);
    };

} // namespace

#endif // __SRTX_SYMBOL_DB_H__
