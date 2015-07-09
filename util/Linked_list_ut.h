#ifndef __util_LINKED_LIST_UT_H__
#define __util_LINKED_LIST_UT_H__

#include <cppunit/extensions/HelperMacros.h>
#include "util/Linked_list.h"

namespace util
{

    class Linked_list_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Linked_list_ut);

        /**
         * @verifies{util-1.7}
         * @verifies{util-1.10}
         */
        CPPUNIT_TEST(test_empty);

        /**
         * @verifies{util-1.3}
         * @verifies{util-1.4}
         * @verifies{util-1.5}
         */
        CPPUNIT_TEST(test_add_front);

        /**
         * @verifies{util-1.3}
         * @verifies{util-1.4}
         * @verifies{util-1.6}
         */
        CPPUNIT_TEST(test_add_back);

        /**
         * @verifies{util-1.1}
         * @verifies{util-1.3}
         * @verifies{util-1.5}
         * @verifies{util-1.6}
         */
        CPPUNIT_TEST(test_iterate_forward);

        /**
         * @verifies{util-1.2}
         * @verifies{util-1.4}
         * @verifies{util-1.5}
         * @verifies{util-1.6}
         */
        CPPUNIT_TEST(test_iterate_reverse);

        /**
         * @verifies{util-1.3}
         * @verifies{util-1.4}
         * @verifies{util-1.5}
         */
        CPPUNIT_TEST(test_delete_front);

        /**
         * @verifies{util-1.5}
         * @verifies{util-1.11}
         */
        CPPUNIT_TEST(test_pop_front);

        /**
         * @verifies{util-1.3}
         * @verifies{util-1.4}
         * @verifies{util-1.5}
         * @verifies{util-1.8}
         */
        CPPUNIT_TEST(test_delete_back);

        /**
         * @verifies{util-1.3}
         * @verifies{util-1.12}
         */
        CPPUNIT_TEST(test_pop_back);

        /**
         * @verifies{util-1.3}
         * @verifies{util-1.5}
         * @verifies{util-1.9}
         */
        CPPUNIT_TEST(test_delete_first_node);

        /**
         * @verifies{util-1.4}
         * @verifies{util-1.5}
         * @verifies{util-1.9}
         */
        CPPUNIT_TEST(test_delete_last_node);

        /**
         * @verifies{util-1.3}
         * @verifies{util-1.4}
         * @verifies{util-1.5}
         * @verifies{util-1.9}
         */
        CPPUNIT_TEST(test_delete_middle_node);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_empty();
        void test_add_front();
        void test_add_back();
        void test_iterate_forward();
        void test_iterate_reverse();
        void test_delete_front();
        void test_pop_front();
        void test_delete_back();
        void test_pop_back();
        void test_delete_first_node();
        void test_delete_last_node();
        void test_delete_middle_node();

      private:
        Linked_list<int> ll;
        Linked_list<int>::Node *ll_node;
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Linked_list_ut);

} // namespace

#endif // __util_LINKED_LIST_UT_H__
