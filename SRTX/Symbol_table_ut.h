#ifndef __SRTX_SYMBOL_TABLE_UT_H__
#define __SRTX_SYMBOL_TABLE_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SRTX {
    class Symbol_table_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Symbol_table_ut);

        CPPUNIT_TEST(test_add_symbol_d);
        CPPUNIT_TEST(test_add_symbol_i);
        CPPUNIT_TEST(test_add_symbol_p);
        CPPUNIT_TEST(test_add_alias);
        CPPUNIT_TEST(test_blocking);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_add_symbol_d();
        void test_add_symbol_i();
        void test_add_symbol_p();

        /**
         * Verify that we can add an alias to an existing symbol table entry
         * and access the entry through that alias.
         */
        void test_add_alias();

        /**
         * Verify that blocking calls to the symbol table work.
         */
        void test_blocking();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Symbol_table_ut);

} // namespace

#endif // __SRTX_SYMBOL_TABLE_UT_H__
