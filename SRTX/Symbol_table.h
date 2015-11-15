#ifndef __SRTX_SYMBOL_TABLE_H__
#define __SRTX_SYMBOL_TABLE_H__

#include "SRTX/Symbol.h"
#include "util/Linked_list.h"

namespace SRTX {
    template <typename T> class Symbol_table {
      public:
        /**
         * Storage for the symbol tables.
         * We create different tables for the different data types.
         */
        typedef Symbol<T> symbol_t;

        typedef util::Linked_list<symbol_t *> list_t;

        /**
         * Constructor.
         */
        Symbol_table() : m_table()
        {
        }

        /**
         * Destructor.
         */
        virtual ~Symbol_table()
        {
        }

        /**
         * Add a symbol to the table.
         * @param name Symbol name.
         * @return A pointer to the symmbol on success or NULL on failure.
         */
        symbol_t *add_symbol(const char *name)
        {
            symbol_t *symbol = new symbol_t(name);
            if((NULL == symbol) || (false == symbol->is_valid())) {
                EPRINTF("Failed to allocate symbol\n");
                delete symbol;
                return NULL;
            }

            m_table.add_front(symbol);
            return symbol;
        }

        /**
         * Return a pointer to a symbol table entry.
         * @param name Symbol name.
         * @return the named symbol table entry on success or NULL if the
         * named symbol is not in the table.
         */
        symbol_t *lookup_symbol(const char *name)
        {
            typename list_t::Node *node = m_table.head();

            DPRINTF("Searching for symbol %s\n", name);
            /* Perform a linear search on the linked list to find the
             * symbol.
             */
            while(node) {
                if(0 == strcmp(name, node->data->get_name())) {
                    DPRINTF("Found symbol %s\n", name);
                    return node->data;
                }

                node = node->next();
            }

            return NULL;
        }

        /**
         * Add an alias for a symbol table entry.
         * An alias is another name (symbol) that we want to assign and be
         * able to access and symbol table entry.
         * @param name Alias.
         * @param entry Entry to be associated with this new symbol.
         */
        symbol_t *alias_symbol(const char *name, symbol_t *symbol)
        {
            if(NULL == symbol) {
                EPRINTF("Attempting to alias a NULL symbol\n");
                return NULL;
            }

            symbol_t *alias = new symbol_t(name, symbol->entry);
            if((NULL == alias) || (false == alias->is_valid())) {
                EPRINTF("Failed to allocate symbol\n");
                delete alias;
                return NULL;
            }

            m_table.add_front(alias);
            return alias;
        }

      private:
        /**
         * Storage for the symbol table.
         */
        list_t m_table;
    };

} // namespace

#endif // __SRTX_SYMBOL_TABLE_H__
