#ifndef __SRTX_DOUBLE_BUFFER_UT_H__
#define __SRTX_DOUBLE_BUFFER_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SRTX {
    class Double_buffer_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Double_buffer_ut);

        CPPUNIT_TEST(test_double_buffer_initialization);
        CPPUNIT_TEST(test_write_and_read_back_value);
        CPPUNIT_TEST(test_write_and_read_value_multiple_times);
        CPPUNIT_TEST(test_read_more_data_than_allocated);
        CPPUNIT_TEST(test_double_buffer_copy);
        CPPUNIT_TEST(test_double_buffer_copy_too_much);
#if 0
        CPPUNIT_TEST_SUITE(test_exhausted_memory);
#endif

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test_double_buffer_initialization();
        void test_write_and_read_back_value();
        void test_write_and_read_value_multiple_times();
        void test_read_more_data_than_allocated();
        void test_double_buffer_copy();
        void test_double_buffer_copy_too_much();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Double_buffer_ut);

} // namespace

#endif // __SRTX_DOUBLE_BUFFER_UT_H__
