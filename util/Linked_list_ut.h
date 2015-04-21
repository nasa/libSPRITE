#ifndef __util_LINKED_LIST_UT_H__
#define __util_LINKED_LIST_UT_H__

#include <cppunit/extensions/HelperMacros.h>
#include "util/Linked_list.h"

namespace util
{

    class Linked_list_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(Linked_list_ut);

        CPPUNIT_TEST(test_add_front);
        CPPUNIT_TEST(test_add_back);
        CPPUNIT_TEST(test_iterate_forward);
        CPPUNIT_TEST(test_iterate_reverse);
        CPPUNIT_TEST(test_delete_front);
        CPPUNIT_TEST(test_delete_back);
        CPPUNIT_TEST(test_delete_first_node);
        CPPUNIT_TEST(test_delete_last_node);
        CPPUNIT_TEST(test_delete_middle_node);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_add_front();
        void test_add_back();
        void test_iterate_forward();
        void test_iterate_reverse();
        void test_delete_front();
        void test_delete_back();
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
