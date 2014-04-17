#include <limits.h>
#include "SRTX/RTC.h"
#include "SRTX/Ring_buffer_ut.h"
#include "SRTX/Ring_buffer.h"

namespace SRTX
{

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
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval+1));
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval+2));
        CPPUNIT_ASSERT_EQUAL(true, rb.write(wval+3));

        /* Attempt to write more data than the buffer can hold
         */
        CPPUNIT_ASSERT_EQUAL(false, rb.write(wval));

        /* Read back values and validate them.
         */
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval+1, rval);
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval+2, rval);
        CPPUNIT_ASSERT_EQUAL(true, rb.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval+3, rval);

        /* Assume that we cannot allocate a ring buffer of type array of the
         * maximum number of ints. (Exhaust memory).
         */
        Base_ring_buffer db_big(INT_MAX - 1, 2);

        CPPUNIT_ASSERT_EQUAL(false, db_big.is_valid());
        CPPUNIT_ASSERT_EQUAL(false, db_big.write(&wval, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(false, db_big.read(&rval, sizeof(int)));

        /* Test blocking timeout.
         */
        units::Nanoseconds now;
        get_time(now);
        CPPUNIT_ASSERT_EQUAL(false, rb.read_blocking(rval, now +
                    units::Nanoseconds(100)));
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

} // namespace
