#ifndef __DEM_DEM_HEADER_UT_H__
#define __DEM_DEM_HEADER_UT_H__

#include <cppunit/extensions/HelperMacros.h>
#include "DEM/DEM_header.h"


namespace DEM
{
    class DEM_header_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(DEM_header_ut);
        CPPUNIT_TEST(test_size);
        CPPUNIT_TEST(test_version_number);
        CPPUNIT_TEST(test_crc_is_present);
        CPPUNIT_TEST(test_sequence_counter_is_present);
        CPPUNIT_TEST(test_secondary_header_is_present);
        CPPUNIT_TEST(test_origin_code);
        CPPUNIT_TEST(test_operation_code);
        CPPUNIT_TEST(test_system_id);
        CPPUNIT_TEST(test_type_id);
        CPPUNIT_TEST(test_content_id);
        CPPUNIT_TEST(test_get_timestamp);
        CPPUNIT_TEST(test_set_timestamp);
        CPPUNIT_TEST(test_timestamp_class);
        CPPUNIT_TEST(test_source_system_id);
        CPPUNIT_TEST(test_source_subsystem_id);
        CPPUNIT_TEST(test_source_system_subsystem);
        CPPUNIT_TEST(test_sequence_count);
        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_size();
        void test_version_number();
        void test_crc_is_present();
        void test_sequence_counter_is_present();
        void test_secondary_header_is_present();
        void test_origin_code();
        void test_operation_code();
        void test_system_id();
        void test_type_id();
        void test_content_id();
        void test_get_timestamp();
        void test_set_timestamp();
        void test_timestamp_class();
        void test_source_system_id();
        void test_source_subsystem_id();
        void test_source_system_subsystem();
        void test_sequence_count();
        void test_get_header_size();

        private:
        DEM_header* header;
        uint8_t* byte;
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(DEM_header_ut);

} // namespace

#endif // __DEM_DEM_HEADER_UT_H__
