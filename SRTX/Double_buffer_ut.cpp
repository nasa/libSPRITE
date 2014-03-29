#include <limits.h>
#include "Double_buffer_ut.h"
#include "Double_buffer.h"

namespace SRTX
{

    void Double_buffer_ut::setUp()
    {
    }


    void Double_buffer_ut::tearDown()
    {
    }


    void Double_buffer_ut::test_double_buffer()
    {
        Double_buffer<int> db;

        CPPUNIT_ASSERT_EQUAL(true, db.is_valid());

        int wval = 9;
        int rval;

        /* Write a value and make sure we can read it back;
         */
        CPPUNIT_ASSERT_EQUAL(true, db.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, db.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);

        /* Do it again.
         */
        CPPUNIT_ASSERT_EQUAL(true, db.write(++wval));
        CPPUNIT_ASSERT_EQUAL(true, db.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);

        /* Attempt to read and write more data than was allocated by the
         * buffer. This test should fail.
         */
        Base_double_buffer* bdb = &db;
        CPPUNIT_ASSERT_EQUAL(false, bdb->read(&wval, sizeof(int) + 1));
        CPPUNIT_ASSERT_EQUAL(false, bdb->write(&wval, sizeof(int) + 1));

        /* Assume that we cannot allocate a double buffer of type array of the
         * maximum number of ints. (Exhaust memory).
         */
        Base_double_buffer db_big(INT_MAX - 1);

        CPPUNIT_ASSERT_EQUAL(false, db_big.is_valid());
        CPPUNIT_ASSERT_EQUAL(false, db_big.write(&wval, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(false, db_big.read(&rval, sizeof(int)));

        /* Test the double buffer copy operation.
         */
        Double_buffer<int> db2;
        wval = 4;
        CPPUNIT_ASSERT_EQUAL(true, db.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, db2.write(0));
        CPPUNIT_ASSERT_EQUAL(true, db.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);
        CPPUNIT_ASSERT_EQUAL(true, db2.read(rval));
        CPPUNIT_ASSERT_EQUAL(0, rval);
        CPPUNIT_ASSERT_EQUAL(true, copy(db2, db, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(true, db2.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);

        /* Now let's try some copy operations that should fail.
         */
        CPPUNIT_ASSERT_EQUAL(false, copy(db2, db, sizeof(int) + 1));
        CPPUNIT_ASSERT_EQUAL(false, copy(db_big, db, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(false, copy(db2, db_big, sizeof(int)));
    }

} // namespace
