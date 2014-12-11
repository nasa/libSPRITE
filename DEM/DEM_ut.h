#ifndef __DEM_DEM_UT_H__
#define __DEM_DEM_UT_H__

#include <cppunit/extensions/HelperMacros.h>
#include "DEM/DEM.h"


namespace DEM
{
    class DEM_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(DEM_ut);
        CPPUNIT_TEST(test_get_header_size);
        CPPUNIT_TEST(test_get_payload_size);
        CPPUNIT_TEST(test_get_payload_pointer);
        CPPUNIT_TEST(test_get_crc_offset);
        CPPUNIT_TEST(test_get_crc);
        CPPUNIT_TEST(test_set_crc);
        CPPUNIT_TEST(test_crc);
        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_get_header_size();
        void test_get_payload_size();
        void test_get_payload_pointer();
        void test_get_crc_offset();
        void test_get_crc();
        void test_set_crc();
        void test_crc();

        private:
        DEM* dem;
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(DEM_ut);

} // namespace

#endif // __DEM_DEM_UT_H__
