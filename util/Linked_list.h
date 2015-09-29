#ifndef __UTIL_LINKED_LIST_H__
#define __UTIL_LINKED_LIST_H__

#include "base/types.h"
#include <stddef.h>

namespace util {
    /**
     * The linked list class is a simple template for creating a doubly linked
     * list data structure.
     * @param T The type of data in the linked list.
     */
    template <typename T> class Linked_list {
      public:
        /**
         * The structure of each node in the linked list.
         */
        class Node {
            /**
             * The owning class must be a friend in order to manipulate
             * the list.
             */
            friend class Linked_list<T>;

          public:
            /**
             * The data stored in the list.
             */
            T data;

            /**
             * Return the next entry in the list.
             * @return The next node in the list.
             * @satisfies{util-1.1}
             */
            Node *next()
            {
                return this->m_next;
            }

            /**
             * Return the previous entry in the list.
             * @return The previous node in the list.
             * @satisfies{util-1.2}
             */
            Node *prev()
            {
                return this->m_prev;
            }

          private:
            /**
             * A pointer to the previous node.
             */
            Node *m_prev;

            /**
             * A pointer to the next node.
             */
            Node *m_next;

            /**
             * Node constructor.
             * @param t Node data.
             * @param p Pointer to the previous node in the list.
             * @param n Pointer to the next node in the list.
             */
            Node(T t, Node *p, Node *n)
                : data(t)
                , m_prev(p)
                , m_next(n)
            {
            }
        };

        /**
         * Construct an empty list empty.
         */
        Linked_list()
            : m_head(NULL)
            , m_tail(NULL)
        {
        }

        /**
         * Test if the list is empty
         * @return true if the list is empty, else false.
         * @satisfies{util-1.10}
         */
        bool is_empty() const
        {
            return NULL == m_head;
        }

        /**
         * Get a pointer to the head of the list.
         * @return Pointer to the head node.
         * @satisfies{util-1.3}
         */
        Node *head() const
        {
            return m_head;
        }

        /**
         * Get a pointer to the tail of the list.
         * @return Pointer to the tail node.
         * @satisfies{util-1.4}
         */
        Node *tail() const
        {
            return m_tail;
        }

        /**
         * Put an element on the front of the list.
         * @param t Data element to add the the list.
         * @satisfies{util-1.5}
         */
        void add_front(T t)
        {
            m_head = new Node(t, NULL, m_head);

            if(m_head->m_next) {
                m_head->m_next->m_prev = m_head;
            }

            if(!m_tail) {
                m_tail = m_head;
            }
        }

        /**
         * Put an element on the tail of the list.
         * @param t Data element to add the the list.
         * @satisfies{util-1.6}
         */
        void add_back(T t)
        {
            m_tail = new Node(t, m_tail, NULL);

            if(m_tail->m_prev) {
                m_tail->m_prev->m_next = m_tail;
            }

            if(!m_head) {
                m_head = m_tail;
            }
        }

        /**
         * Remove an element from the front of the list.
         * @satisfies{util-1.7}
         */
        void delete_front()
        {
            if(!m_head) {
                return;
            }

            Node *temp(m_head);
            m_head = m_head->m_next;

            if(m_head) {
                m_head->m_prev = NULL;
            } else {
                m_tail = NULL;
            }

            delete temp;
        }

        /**
         * Pop an element from the front of the list.
         * @param t Returned value from the list.
         * @return true if an element was returned, else false.
         * @satisfies{util-1.11}
         */
        bool pop_front(T &t)
        {
            if(NULL == m_head) {
                return false;
            }

            t = m_head->data;

            delete_front();

            return true;
        }

        /**
         * Remove an element from the tail of the list.
         * @param t Data element to add the the list.
         * @satisfies{util-1.8}
         */
        void delete_back()
        {
            if(!m_tail) {
                return;
            }

            Node *temp(m_tail);
            m_tail = m_tail->m_prev;

            if(m_tail) {
                m_tail->m_next = NULL;
            } else {
                m_head = NULL;
            }

            delete temp;
        }

        /**
         * Pop an element from the back of the list.
         * @param t Returned value from the list.
         * @return true if an element was returned, else false.
         * @satisfies{util-1.12}
         */
        bool pop_back(T &t)
        {
            if(NULL == m_tail) {
                return false;
            }

            t = m_tail->data;

            delete_back();

            return true;
        }

        /**
         * Remove the given node from the linked list.
         * @param node The node to be deleted.
         */
        void delete_node(Node *node)
        {
            /* Handle the case where the node is the first element in
             * the list.
             */
            if(node == m_head) {
                delete_front();
                node = NULL;
                return;
            }

            /* Handle the case where the node is the last element in
             * the list.
             */
            if(node == m_tail) {
                delete_back();
                node = NULL;
                return;
            }

            /* All other cases.
             */
            node->m_prev->m_next = node->m_next;
            node->m_next->m_prev = node->m_prev;

            delete node;
            node = NULL;
        }

      private:
        /**
         * The first node in the list.
         */
        Node *m_head;

        /**
         * The last node in the list.
         */
        Node *m_tail;
    };

/* This code was supposed to reduce code bloat by mapping all pointers to a
 * single instantiation of the template. With only a couple of pointer
 * types being stored, it actually made the code size bigger. I think it
 * may be because of the nested Node class, but that's just a guess. -DLH
 */
#if 0
    /**
     * The linked list class is a simple template for creating a doubly linked
     * list data structure. This is optimized for pointers.
     * @param T The type of data in the linked list.
     */
    template<>
    class Linked_list<void *>
    {
        public:
            /**
             * The structure of each node in the linked list.
             */
            class Node
            {
                /**
                 * The owning class must be a friend in order to manipulate
                 * the list.
                 */
                friend class Linked_list<void *>;

                public:
                /**
                 * The data stored in the list.
                 */
                void* data;

                /**
                 * Prefix increment operator.
                 * @return The next node in the list.
                 */
                Node* next()
                {
                    return this->m_next;
                }

                Node* prev()
                {
                    return this->m_prev;
                }

                protected:
                /**
                 * A pointer to the previous node.
                 */
                Node* m_prev;

                /**
                 * A pointer to the next node.
                 */
                Node* m_next;

                /**
                 * Node constructor.
                 * @param t Node data.
                 * @param p Pointer to the previous node in the list.
                 * @param n Pointer to the next node in the list.
                 */
                Node(void* t, Node* p, Node* n) :
                    data(t),
                    m_prev(p),
                    m_next(n)
                {
                }
            };

            /**
             * Construct a queue, initialize as
             * empty.
             */
            Linked_list() :
                m_head(NULL),
                m_tail(NULL)
        {
        }

            /**
             * Get a pointer to the head of the list.
             * @return Pointer to the head node.
             */
            Node* head() const
            {
                return m_head;
            }

            /**
             * Get a pointer to the tail of the list.
             * @return Pointer to the tail node.
             */
            Node* tail() const
            {
                return m_tail;
            }

            /**
             * Put an element on the front of the list.
             * @param t Data element to add the the list.
             */
            void add_front(void* t)
            {
                m_head = new Node(t, NULL, m_head);

                if(m_head->m_next)
                {
                    m_head->m_next->m_prev = m_head;
                }

                if(!m_tail)
                {
                    m_tail = m_head;
                }
            }

            /**
             * Put an element on the tail of the list.
             * @param t Data element to add the the list.
             */
            void add_back(void* t)
            {
                m_tail = new Node(t, m_tail, NULL);

                if(m_tail->m_prev)
                {
                    m_tail->m_prev->m_next = m_tail;
                }

                if(!m_head)
                {
                    m_head = m_tail;
                }
            }

            /**
             * Remove an element from the front of the list.
             */
            void delete_front()
            {
                if(!m_head)
                {
                    return;
                }

                Node* temp(m_head);
                m_head = m_head->m_next;

                if(m_head)
                {
                    m_head->m_prev = NULL;
                }
                else
                {
                    m_tail = NULL;
                }

                delete temp;
            }

            /**
             * Remove an element from the tail of the list.
             * @param t Data element to add the the list.
             */
            void delete_back()
            {
                if(!m_tail)
                {
                    return;
                }

                Node* temp(m_tail);
                m_tail = m_tail->m_prev;

                if(m_tail)
                {
                    m_tail->m_next = NULL;
                }
                else
                {
                    m_head = NULL;
                }

                delete temp;
            }

        private:
            /**
             * The first node in the list.
             */
            Node* m_head;

            /**
             * The last node in the list.
             */
            Node* m_tail;
    };

    /**
     * The linked list class is a simple template for creating a doubly linked
     * list data structure. This is optimized for pointers.
     * @param T The type of data in the linked list.
     */
    template<typename T>
        class Linked_list<T*> : private Linked_list<void*>
        {
            typedef Linked_list<void*> void_Linked_list;
            public:

            class Node
            {
                /**
                 * The owning class must be a friend in order to manipulate
                 * the list.
                 */
                friend class Linked_list<T*>;

                public:
                /**
                 * The data stored in the list.
                 */
                T* data;

                /**
                 * Prefix increment operator.
                 * @return The next node in the list.
                 */
                Node* next()
                {
                    return this->m_next;
                }

                Node* prev()
                {
                    return this->m_prev;
                }

                private:
                /**
                 * A pointer to the previous node.
                 */
                Node* m_prev;

                /**
                 * A pointer to the next node.
                 */
                Node* m_next;

                /**
                 * Node constructor.
                 * @param t Node data.
                 * @param p Pointer to the previous node in the list.
                 * @param n Pointer to the next node in the list.
                 */
                Node(T* t, Node* p, Node* n) :
                    data(t),
                    m_prev(p),
                    m_next(n)
                {
                }
            };

            /**
             * Construct a queue, initialize as
             * empty.
             */
            Linked_list()
            {
            }

            /**
             * Get a pointer to the head of the list.
             * @return Pointer to the head node.
             */
            Node* head() const
            {
                return (Node*) void_Linked_list::head();
            }

            /**
             * Get a pointer to the tail of the list.
             * @return Pointer to the tail node.
             */
            Node* tail() const
            {
                return void_Linked_list::tail();
            }

            /**
             * Put an element on the front of the list.
             * @param t Data element to add the the list.
             */
            void add_front(T* t)
            {
                void_Linked_list::add_front(t);
            }

            /**
             * Put an element on the tail of the list.
             * @param t Data element to add the the list.
             */
            void add_back(T* t)
            {
                void_Linked_list::add_back(t);
            }

            /**
             * Remove an element from the front of the list.
             */
            void delete_front()
            {
                void_Linked_list::delete_front();
            }

            /**
             * Remove an element from the tail of the list.
             * @param t Data element to add the the list.
             */
            void delete_back()
            {
                void_Linked_list::delete_front();
            }

        };
#endif

} // namespace

#endif // __UTIL_LINKED_LIST_H__
