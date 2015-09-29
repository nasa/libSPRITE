#include "util/Linked_list_ut.h"

namespace util {
    Linked_list_ut::Linked_list_ut()
        : ll()
        , ll_node(NULL)
    {
    }

    void Linked_list_ut::setUp()
    {
    }

    void Linked_list_ut::tearDown()
    {
    }

    void Linked_list_ut::test_empty()
    {
        Linked_list<float> local_ll;
        CPPUNIT_ASSERT_EQUAL(true, local_ll.is_empty());

        local_ll.add_front(1.2);
        CPPUNIT_ASSERT_EQUAL(false, local_ll.is_empty());
    }

    void Linked_list_ut::test_add_front()
    {
        ll.add_front(3);
        ll.add_front(2);
        ll.add_front(1);

        ll_node = ll.head();
        CPPUNIT_ASSERT_EQUAL(1, ll_node->data);

        ll_node = ll.tail();
        CPPUNIT_ASSERT_EQUAL(3, ll_node->data);
    }

    void Linked_list_ut::test_add_back()
    {
        ll.add_back(1);
        ll.add_back(2);
        ll.add_back(3);
        ll_node = ll.tail();

        CPPUNIT_ASSERT_EQUAL(3, ll_node->data);

        ll_node = ll.head();
        CPPUNIT_ASSERT_EQUAL(1, ll_node->data);
    }

    void Linked_list_ut::test_iterate_forward()
    {
        ll.add_front(3);
        ll.add_front(2);
        ll.add_front(1);
        ll.add_back(4);

        int i = 1;
        ll_node = ll.head();
        while(ll_node) {
            CPPUNIT_ASSERT_EQUAL(ll_node->data, i);
            ll_node = ll_node->next();
            ++i;
        }
        CPPUNIT_ASSERT_EQUAL(5, i);
    }

    void Linked_list_ut::test_iterate_reverse()
    {
        ll.add_back(2);
        ll.add_back(3);
        ll.add_back(4);
        ll.add_front(1);

        int i = 4;
        ll_node = ll.tail();
        while(ll_node) {
            CPPUNIT_ASSERT_EQUAL(ll_node->data, i);
            ll_node = ll_node->prev();
            --i;
        }
        CPPUNIT_ASSERT_EQUAL(0, i);
    }

    void Linked_list_ut::test_delete_front()
    {
        ll.add_front(3);
        ll.add_front(2);
        ll.add_front(1);

        ll.delete_front();
        ll_node = ll.head();
        CPPUNIT_ASSERT_EQUAL(2, ll_node->data);

        ll.delete_front();
        ll_node = ll.head();
        CPPUNIT_ASSERT_EQUAL(3, ll_node->data);

        ll_node = ll.tail();
        CPPUNIT_ASSERT_EQUAL(3, ll_node->data);

        ll.delete_front();
        ll_node = ll.head();
        CPPUNIT_ASSERT(NULL == ll_node);

        ll_node = ll.tail();
        CPPUNIT_ASSERT(NULL == ll_node);
    }

    void Linked_list_ut::test_pop_front()
    {
        ll.add_front(2);
        ll.add_front(1);

        int data;

        CPPUNIT_ASSERT_EQUAL(true, ll.pop_front(data));
        CPPUNIT_ASSERT_EQUAL(1, data);

        CPPUNIT_ASSERT_EQUAL(true, ll.pop_front(data));
        CPPUNIT_ASSERT_EQUAL(2, data);

        CPPUNIT_ASSERT_EQUAL(false, ll.pop_front(data));
    }

    void Linked_list_ut::test_delete_back()
    {
        ll.add_front(3);
        ll.add_front(2);
        ll.add_front(1);

        ll.delete_back();
        ll_node = ll.tail();
        CPPUNIT_ASSERT_EQUAL(2, ll_node->data);

        ll.delete_back();
        ll_node = ll.head();
        CPPUNIT_ASSERT_EQUAL(1, ll_node->data);

        ll_node = ll.tail();
        CPPUNIT_ASSERT_EQUAL(1, ll_node->data);

        ll.delete_back();
        ll_node = ll.head();
        CPPUNIT_ASSERT(NULL == ll_node);

        ll_node = ll.tail();
        CPPUNIT_ASSERT(NULL == ll_node);
    }

    void Linked_list_ut::test_pop_back()
    {
        ll.add_front(2);
        ll.add_front(1);

        int data;

        CPPUNIT_ASSERT_EQUAL(true, ll.pop_back(data));
        CPPUNIT_ASSERT_EQUAL(2, data);

        CPPUNIT_ASSERT_EQUAL(true, ll.pop_back(data));
        CPPUNIT_ASSERT_EQUAL(1, data);

        CPPUNIT_ASSERT_EQUAL(false, ll.pop_back(data));
    }

    void Linked_list_ut::test_delete_first_node()
    {
        ll.add_front(3);
        ll.add_front(2);
        ll.add_front(1);

        ll_node = ll.head();

        ll.delete_node(ll_node);
        ll_node = ll.head();
        CPPUNIT_ASSERT_EQUAL(2, ll_node->data);
    }

    void Linked_list_ut::test_delete_last_node()
    {
        ll.add_front(3);
        ll.add_front(2);
        ll.add_front(1);

        ll_node = ll.tail();

        ll.delete_node(ll_node);
        ll_node = ll.tail();
        CPPUNIT_ASSERT_EQUAL(2, ll_node->data);
    }

    void Linked_list_ut::test_delete_middle_node()
    {
        ll.add_front(3);
        ll.add_front(2);
        ll.add_front(1);

        ll_node = ll.tail();
        ll_node = ll_node->prev();

        ll.delete_node(ll_node);

        ll_node = ll.tail();
        CPPUNIT_ASSERT_EQUAL(3, ll_node->data);

        ll_node = ll_node->prev();
        CPPUNIT_ASSERT_EQUAL(1, ll_node->data);

        ll_node = ll.head();
        CPPUNIT_ASSERT_EQUAL(1, ll_node->data);

        ll_node = ll_node->next();
        CPPUNIT_ASSERT_EQUAL(3, ll_node->data);
    }

#if 0
    /* Define some types to be used in the test below.
     */
    struct a
    {
        int a_a;
    };
    struct b
    {
        int b_b;
    };
    struct c
    {
        int c_c;
    };
    struct d
    {
        int d_d;
    };

    /* This is not an executable test. It just here to check to see if template
     * specialization for pointers actually reduces code bloat.
     */
    void test_code_size()
    {
        Linked_list<struct a*> ll_a;
        Linked_list<struct b*> ll_b;
        Linked_list<struct c*> ll_c;
        Linked_list<struct d*> ll_d;

        void * ptr;

        ptr = ll_a.head();
        ptr = ll_b.head();
        ptr = ll_c.head();
        ptr = ll_d.head();

    }
#endif

} // namespace
