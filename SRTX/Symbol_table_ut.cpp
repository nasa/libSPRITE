#include <signal.h>
#include <unistd.h>
#include "SRTX/RTC.h"
#include "SRTX/Symbol_table_ut.h"
#include "SRTX/Symbol_db.h"

namespace SRTX {

    void Symbol_table_ut::setUp()
    {
    }

    void Symbol_table_ut::tearDown()
    {
    }

    void Symbol_table_ut::test_add_symbol_d()
    {
        Symbol_table<double> tbl;
        Symbol_table<double>::symbol_t *symbol;
        const char *sym_name = "d";
        double d = 1.14;
        double dtmp = 3.14;

        /* The symbol hasn't been added to the table so we expect it to fail.
         */
        symbol = tbl.lookup_symbol(sym_name);
        CPPUNIT_ASSERT(NULL == symbol);

        /* Add the symbol to the table.
         */
        symbol = tbl.add_symbol(sym_name);
        CPPUNIT_ASSERT(symbol != NULL);
        CPPUNIT_ASSERT_EQUAL(true, symbol->is_valid());

        /* Assigning a value to the symbolic entry should return true if the
         * symbol exists.
         */
        CPPUNIT_ASSERT_EQUAL(true, symbol->entry->write(dtmp));

        /* Test that the symbol has the expected value.
         */
        CPPUNIT_ASSERT_EQUAL(true, symbol->entry->read(dtmp));
        CPPUNIT_ASSERT_EQUAL(3.14, dtmp);
        CPPUNIT_ASSERT_EQUAL(true, symbol->entry->read(d));
        CPPUNIT_ASSERT_EQUAL(dtmp, d);
    }

    void Symbol_table_ut::test_add_symbol_i()
    {
        Symbol_db<int> &tbl = Symbol_db<int>::get_instance();
        Symbol_table<int>::symbol_t *symbol_a;
        Symbol_table<int>::symbol_t *symbol_b;
        const char *sym1 = "int_a";
        const char *sym2 = "int_b";
        int a = 1;
        int b = 2;

        /* Add the two symbols and check there values.
         */
        symbol_a = tbl.add_symbol(sym1);
        symbol_b = tbl.add_symbol(sym2);
        CPPUNIT_ASSERT(symbol_a != NULL);
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->is_valid());
        CPPUNIT_ASSERT(symbol_b != NULL);
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->is_valid());
        int atmp;
        int btmp;
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->entry->write(a));
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->entry->read(atmp));
        CPPUNIT_ASSERT_EQUAL(a, atmp);
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->entry->write(b));
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->entry->read(btmp));
        CPPUNIT_ASSERT_EQUAL(b, btmp);

        /* Use the temporary variables to swap the symbolic entries.
         */
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->entry->write(btmp));
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->entry->write(atmp));
        CPPUNIT_ASSERT(a != btmp);
        CPPUNIT_ASSERT(b != atmp);
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->entry->read(a));
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->entry->read(b));
        CPPUNIT_ASSERT_EQUAL(a, btmp);
        CPPUNIT_ASSERT_EQUAL(b, atmp);
    }

    void Symbol_table_ut::test_add_symbol_p()
    {
        Symbol_table<int *> tbl;
        Symbol_table<int *>::symbol_t *symbol_a;
        Symbol_table<int *>::symbol_t *symbol_b;
        const char *sym1 = "int_a";
        const char *sym2 = "int_b";
        int *a = new int;
        int *b = new int;

        *a = 1;
        *b = 2;

        /* Add the two symbols and check there values.
         */
        symbol_a = tbl.add_symbol(sym1);
        symbol_b = tbl.add_symbol(sym2);
        CPPUNIT_ASSERT(symbol_a != NULL);
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->is_valid());
        CPPUNIT_ASSERT(symbol_b != NULL);
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->is_valid());
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->entry->write(a));
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->entry->write(b));
        int *atmp;
        int *btmp;
        CPPUNIT_ASSERT_EQUAL(true, symbol_a->entry->read(atmp));
        CPPUNIT_ASSERT_EQUAL(a, atmp);
        CPPUNIT_ASSERT_EQUAL(*a, *atmp);
        CPPUNIT_ASSERT_EQUAL(true, symbol_b->entry->read(btmp));
        CPPUNIT_ASSERT_EQUAL(b, btmp);
        CPPUNIT_ASSERT_EQUAL(*b, *btmp);
    }

    void Symbol_table_ut::test_add_alias()
    {
        Symbol_db<int> &tbl = Symbol_db<int>::get_instance();
        char alias[] = "frijole";

        /* Attempting to assign an alias to a NULL symbol should fail.
         */
        Symbol_table<int>::symbol_t *sym;
        IPRINTF("\nThis test is expected to generate an error message.\n");
        sym = tbl.alias_symbol(alias, NULL);
        CPPUNIT_ASSERT(NULL == sym);

        /* Lookup an existing entry and enter it in the table as an alias.
         */
        char sym_name[] = "int_a";
        Symbol_table<int>::symbol_t *sym_a;
        sym_a = tbl.lookup_symbol(sym_name);
        CPPUNIT_ASSERT(sym_a != NULL);
        CPPUNIT_ASSERT_EQUAL(true, sym_a->is_valid());

        /* Associate the symbol with the alias.
         */
        sym = tbl.alias_symbol(alias, sym_a);
        CPPUNIT_ASSERT(NULL != sym);
        CPPUNIT_ASSERT_EQUAL(true, sym->is_valid());

        /* Make sure the alias value is the same as the original value.
         */
        int a;
        int alias_a;
        CPPUNIT_ASSERT_EQUAL(true, sym->entry->read(alias_a));
        CPPUNIT_ASSERT_EQUAL(true, sym_a->entry->read(a));
        CPPUNIT_ASSERT_EQUAL(a, alias_a);

        /* Change a and make sure the value is reflected in the alias.
         */
        CPPUNIT_ASSERT_EQUAL(true, sym_a->entry->write(++a));
        CPPUNIT_ASSERT(a != alias_a);
        CPPUNIT_ASSERT_EQUAL(true, sym->entry->read(alias_a));
        CPPUNIT_ASSERT_EQUAL(a, alias_a);

        /* Change alias_a and make sure the value is reflected in a.
         */
        CPPUNIT_ASSERT_EQUAL(true, sym->entry->write(++alias_a));
        CPPUNIT_ASSERT(a != alias_a);
        CPPUNIT_ASSERT_EQUAL(true, sym_a->entry->read(a));
        CPPUNIT_ASSERT_EQUAL(a, alias_a);
    }

    void sigcatcher(int sig)
    {
        const char *sym_name = "int_blocking";
        typedef Symbol_db<int> sym_tbl_t;
        static sym_tbl_t &tbl = sym_tbl_t::get_instance();
        static Symbol_table<int>::symbol_t *sym = tbl.lookup_symbol(sym_name);
        static int a(9);

        if(SIGALRM == sig) {
            CPPUNIT_ASSERT_EQUAL(true, sym->entry->write(++a));
        }
    }

    void Symbol_table_ut::test_blocking()
    {
        typedef Symbol_db<int> sym_tbl_t;
        sym_tbl_t &tbl = sym_tbl_t::get_instance();

        char sym_name[] = "int_blocking";
        Symbol_table<int>::symbol_t *sym = tbl.add_symbol(sym_name);

        /* Verify that we can set and get the value and the basic timeout call
         * works.
         */
        int a(42);
        CPPUNIT_ASSERT_EQUAL(true, sym->entry->write(a));
        units::Nanoseconds now;
        get_time(now);
        CPPUNIT_ASSERT_EQUAL(
            true, sym->entry->read_blocking(a, now + units::Nanoseconds(100)));
        CPPUNIT_ASSERT_EQUAL(42, a);

        /* Set up the alarm.
         */
        struct sigaction sact;
        sigemptyset(&sact.sa_mask);
        sact.sa_flags = 0;
        sact.sa_handler = sigcatcher;
        sigaction(SIGALRM, &sact, NULL);

        /* Set timer to increment and update the symbol value.
         */
        alarm(1);
        // Block until we get an update.
        CPPUNIT_ASSERT_EQUAL(true, sym->entry->read_blocking(a));
        CPPUNIT_ASSERT_EQUAL(10, a);

        /* Set timer to increment and update the symbol value.
         */
        alarm(1);
        // This one should time out early.
        get_time(now);
        CPPUNIT_ASSERT_EQUAL(
            true, sym->entry->read_blocking(a, now + units::Nanoseconds(100)));
        CPPUNIT_ASSERT_EQUAL(10, a);
        // This one should get an updated (incremented) value.
        get_time(now);
        CPPUNIT_ASSERT_EQUAL(
            true,
            sym->entry->read_blocking(a, now + units::Nanoseconds(units::SEC)));
        alarm(0);
        CPPUNIT_ASSERT_EQUAL(11, a);
    }

} // namespace
