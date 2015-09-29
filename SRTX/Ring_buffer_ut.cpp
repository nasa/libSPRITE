#include <limits.h>
#include "SRTX/RTC.h"
#include "SRTX/Ring_buffer_ut.h"
#include "SRTX/Ring_buffer.h"

namespace SRTX {

    void Ring_buffer_ut::setUp()
    {
    }

    void Ring_buffer_ut::tearDown()
    {
    }

    void Ring_buffer_ut::test_ring_buffer()
    {
        Ring_buffer<int> rb(3);

        CPPUNIT_ASSERT_EQUAL(true, rb.is_valid());

        int wval = 9;
        int rval;

        /* Write a value and make sure we can read it back;
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);

        /* Do it again.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(++wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);

        /* Fill the buffer.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval + 1));
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval + 2));
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval + 3));

        /* Attempt to write more data than the buffer can hold
         */
        CPPUNIT_ASSERT_EQUAL(false, rb.write(wval));

        /* Read back values and validate them.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval + 1, rval);
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval + 2, rval);
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval + 3, rval);

#if 0 // Not repeatable. Some machines can allocate that much RAM.
        /* Assume that we cannot allocate a ring buffer of type array of the
         * maximum number of ints. (Exhaust memory).
         */
        Base_ring_buffer db_big(INT_MAX - 1, 2);

        CPPUNIT_ASSERT_EQUAL(false, db_big.is_valid());
        CPPUNIT_ASSERT_EQUAL(false, db_big.write(&wval, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(false, db_big.read(&rval, sizeof(int)));
#endif

        /* Test blocking timeout.
         */
        units::Nanoseconds now;
        get_time(now);
        CPPUNIT_ASSERT_EQUAL(
            false, rb.read_blocking(rval, now + units::Nanoseconds(100)));
    }

    void Ring_buffer_ut::test_empty()
    {
        Ring_buffer<int> rb(3);
        int wval = 1;

        /* Starts empty so empty should be true.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.is_valid());
        CPPUNIT_ASSERT_EQUAL(true, rb.is_empty());

        /* Write something in and make sure the buffer does not report empty.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_empty());

        /* Write until the buffer is full and make sure it doesn't report empty.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_empty());

        /* I shouldn't be able to write anymore.
         */
        CPPUNIT_ASSERT_EQUAL(false, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_empty());

        /* Now drain the buffer.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_empty());
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_empty());
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.is_empty());

        /* Try to read to much.
         */
        CPPUNIT_ASSERT_EQUAL(false, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.is_empty());
    }

    void Ring_buffer_ut::test_full()
    {
        Ring_buffer<int> rb(3);
        int wval = 1;

        /* Starts empty so is_full() should be false.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.is_valid());
        CPPUNIT_ASSERT_EQUAL(false, rb.is_full());

        /* Write something in and make sure the buffer is not yet full.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_full());

        /* Write two more times and it should be full.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.is_full());

        /* Try to write again. Should fail and still be full.
         */
        CPPUNIT_ASSERT_EQUAL(false, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.is_full());

        /* Read a value. Should not be full anymore.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_full());

        /* Read the rest of the data. Should not be full.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_full());

        /* Try to read too much.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.is_empty());
        CPPUNIT_ASSERT_EQUAL(false, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(false, rb.is_full());
    }

    void Ring_buffer_ut::test_count()
    {
        Ring_buffer<int> rb(3);
        int wval = 1;

        /* Starts empty.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.is_valid());
        CPPUNIT_ASSERT_EQUAL(0u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(3u, rb.nelems_free());

        /* Write and check that the counts change correctly.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(1u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(2u, rb.nelems_free());
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(2u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(1u, rb.nelems_free());
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(3u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(0u, rb.nelems_free());

        /* Buffer is full, writing should not change the count.
         */
        CPPUNIT_ASSERT_EQUAL(false, rb.write(wval));
        CPPUNIT_ASSERT_EQUAL(3u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(0u, rb.nelems_free());

        /* Start reading and make sure the counts make sense.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(2u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(1u, rb.nelems_free());
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(1u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(2u, rb.nelems_free());
        CPPUNIT_ASSERT_EQUAL(true, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(0u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(3u, rb.nelems_free());

        /* Buffer is empty now. Try to read again. Counts should not change.
         */
        CPPUNIT_ASSERT_EQUAL(false, rb.read(wval));
        CPPUNIT_ASSERT_EQUAL(0u, rb.nelems_used());
        CPPUNIT_ASSERT_EQUAL(3u, rb.nelems_free());
    }

} // namespace
