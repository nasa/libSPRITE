#include <limits.h>
#include "SRTX/Double_buffer_ut.h"
#include "SRTX/Double_buffer.h"

namespace SRTX {

    void Double_buffer_ut::setUp()
    {
    }

    void Double_buffer_ut::tearDown()
    {
    }

    void Double_buffer_ut::test_double_buffer_initialization()
    {
        Double_buffer<int> db;

        CPPUNIT_ASSERT_EQUAL(true, db.is_valid());
    }

    void Double_buffer_ut::test_write_and_read_back_value()
    {
        Double_buffer<int> db;
        int wval = 9;
        int rval;

        /* Write a value and make sure we can read it back;
         */
        CPPUNIT_ASSERT_EQUAL(true, db.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, db.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);
    }

    void Double_buffer_ut::test_write_and_read_value_multiple_times()
    {
        Double_buffer<int> db;
        int wval = 9;
        int rval;

        for(int i = 0; i < 3; i++) {
            /* Write a value and make sure we can read it back;
             */
            CPPUNIT_ASSERT_EQUAL(true, db.write(wval));
            CPPUNIT_ASSERT_EQUAL(true, db.read(rval));
            CPPUNIT_ASSERT_EQUAL(wval, rval);
            /* Then do it again.
             */
        }
    }

    void Double_buffer_ut::test_read_more_data_than_allocated()
    {
        Double_buffer<int> db;
        Base_double_buffer *bdb = &db;
        int wval = 9;
        int rval;

        /* Attempt to read and write more data than was allocated by the
         * buffer. This test should fail.
         */
        CPPUNIT_ASSERT_EQUAL(false, bdb->read(&wval, sizeof(int) + 1));
        CPPUNIT_ASSERT_EQUAL(false, bdb->write(&wval, sizeof(int) + 1));
    }

#if 0 // Not repeatable with some machines.
    void Double_buffer_ut::test_exhausted_memory()
    {
        /* Assume that we cannot allocate a double buffer of type array of the
         * maximum number of ints. (Exhaust memory).
         */
        Base_double_buffer db_big(UINT_MAX);

        CPPUNIT_ASSERT_EQUAL(false, db_big.is_valid());
        CPPUNIT_ASSERT_EQUAL(false, db_big.write(&wval, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(false, db_big.read(&rval, sizeof(int)));
    }
#endif

    void Double_buffer_ut::test_double_buffer_copy()
    {
        Double_buffer<int> db;
        Double_buffer<int> db2;
        int wval = 4;
        int rval;

        /* Test the double buffer copy operation.
         */
        CPPUNIT_ASSERT_EQUAL(true, db.write(wval));
        CPPUNIT_ASSERT_EQUAL(true, db2.write(0));
        CPPUNIT_ASSERT_EQUAL(true, db.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);
        CPPUNIT_ASSERT_EQUAL(true, db2.read(rval));
        CPPUNIT_ASSERT_EQUAL(0, rval);
        CPPUNIT_ASSERT_EQUAL(true, copy_entry(db2, db, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(true, db2.read(rval));
        CPPUNIT_ASSERT_EQUAL(wval, rval);
    }

    void Double_buffer_ut::test_double_buffer_copy_too_much()
    {
        Double_buffer<int> db;
        Double_buffer<int> db2;

        /* Now let's try some copy operations that should fail.
         */
        CPPUNIT_ASSERT_EQUAL(false, copy_entry(db2, db, sizeof(int) + 1));
#if 0
        CPPUNIT_ASSERT_EQUAL(false, copy_entry(db_big, db, sizeof(int)));
        CPPUNIT_ASSERT_EQUAL(false, copy_entry(db2, db_big, sizeof(int)));
#endif
    }

} // namespace
