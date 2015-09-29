#ifndef __SRTX_SYMBOL_H__
#define __SRTX_SYMBOL_H__

#include <string.h>
#include "SRTX/Double_buffer.h"
#include "base/XPRINTF.h"

namespace SRTX {

#ifndef SYM_ENTRY_STRLEN
    const unsigned int SYM_ENTRY_STRLEN = 256;
#endif

    template <typename T> class Symbol {
      public:
        /**
         * Constructor for symbolic entries.
         * @param sym_name Entry name.
         * @param sym_entry The symbolic data.
         */
        Symbol(const char *sym_name, Double_buffer<T> *sym_entry = NULL)
            : entry(sym_entry)
            , m_valid(false)
        {
            /* Make sure that the symbol name is not too long to be stored.
             */
            if(strlen(sym_name) > SYM_ENTRY_STRLEN) {
                EPRINTF("Symbol name %s is too long\n", sym_name);
                return;
            }

            /* If no entry was passed in, allocate one.
            */
            if(NULL == entry) {
                entry = new Double_buffer<T>;
                static T ival;
                entry->write(ival);
            }

            if((NULL == entry) || (false == entry->is_valid())) {
                EPRINTF("Invalid symbol table data\n");
                delete entry;
                return;
            }

            /* Set the entry name.
            */
            strncpy(m_name, sym_name, SYM_ENTRY_STRLEN);

            m_valid = true;
            DPRINTF("Created new symbol %s\n", m_name);
        }

        /**
         * Indicate if this class is valid.
         * @return True if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

        /**
         * Get name.
         * Get the name of the symbol table entry.
         * @return The entry name.
         */
        const char *get_name() const
        {
            return m_name;
        }

        /**
         * Storage for the data associated with the symbol.
         */
        Double_buffer<T> *entry;

      private:
        /**
         * Indicator of class validity.
         */
        bool m_valid;

        /**
         * Symbol name.
         * Add one for the NUL string terminator.
         */
        char m_name[SYM_ENTRY_STRLEN + 1];
    };

} // namespace

#endif // __SRTX_SYMBOL_H__
