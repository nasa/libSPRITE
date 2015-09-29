#ifndef __UTIL_SAMPLE_SET_H__
#define __UTIL_SAMPLE_SET_H__

#include <stdlib.h>
#include "base/assertion.h"

namespace util {

    /**
     * This class keeps track of the last 'n' samples of data.
     */
    template <typename T> class Sample_set {

      public:
        /**
         * Constructor.
         * @param nelem Number of elements that can be stored in the
         * buffer.
         * @satisfies{util-2.1}
         */
        Sample_set(unsigned int nelem)
            : m_elem(static_cast<T *>(malloc(sizeof(T) * nelem)))
            , m_nelem((NULL == m_elem) ? 0 : nelem)
            , m_head(nelem - 1)
            , m_npop(0)
        {
        }

        /**
         * Destructor.
         */
        ~Sample_set()
        {
            m_nelem = m_npop = 0;
            free(m_elem);
            m_elem = NULL;
        }

        /**
         * Return indication as to whether this class is valid.
         * @return True if valid, else false.
         */
        bool is_valid() const
        {
            static bool valid = m_nelem != 0;
            return valid;
        }

        /**
         * Return the number of elements in a sample set.
         * @return Number of elements or 0 if invalid.
         * @satisfies{util-2.2}
         */
        unsigned int nelem() const
        {
            return m_nelem;
        }

        /**
         * Test if the sample set is full.
         * @return True if full, else false.
         * @satisfies{util-2.3}
         */
        bool is_full() const
        {
            return m_nelem == m_npop;
        }

        /**
         * Return the number of elements populated.
         * @return The number of elements that have been populated.
         * @satisfies{util-2.4}
         */
        unsigned int npopulated() const
        {
            return m_npop;
        }

        /**
         * Operator overload for accessing an element.
         * Used like this: double x = S(i);
         * @note The most recent element is 1.
         * @param i Element to access.
         * @return Eelement value.
         */
        T operator()(unsigned int i) const
        {
            assert((i >= 1) && (i <= m_nelem));

            int elem = (m_head - i + 1);
            if(elem < 0) {
                elem += m_nelem;
            }
            return m_elem[elem];
        }

        /**
         * Add a new sample to the sample set. If the sample set is full,
         * the oldest sample will be replaced.
         * @param val Sample value to store.
         * @satisfies{util-2.5}
         * @satisfies{util-2.6}
         */
        void push(const T val)
        {
            /* Move the head pointer.
             */
            m_head = (m_head + 1) % m_nelem;

            /* Add the new sample.
             */
            m_elem[m_head] = val;

            /* Increment the number of samples populated if necessary.
             */
            if(m_npop < m_nelem) {
                ++m_npop;
            }
        }

      private:
        /**
         * Copy constructor.
         * The copy constructor is made private to prevent copy because the
         * class has a pointer member variable.
         */
        Sample_set(const Sample_set &);

        /**
         * Assignment operator.
         * The assignment operator is made private to because the class has a
         * pointer member variable.
         */
        Sample_set &operator=(const Sample_set &);

        /**
         * Buffer elements.
         */
        T *m_elem;

        /**
         * Number of elements.
         */
        unsigned int m_nelem;

        /**
         * Index of the first element.
         */
        unsigned int m_head;

        /**
         * Number of sample positions populated.
         */
        unsigned int m_npop;
    };

} // namespace

#endif // __UTIL_SAMPLE_SET_H__
