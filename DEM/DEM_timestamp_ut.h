#ifndef __DEM_DEM_TIMESTAMP_UT_H__
#define __DEM_DEM_TIMESTAMP_UT_H__

#include <cppunit/extensions/HelperMacros.h>
#include "DEM/DEM_timestamp.h"


namespace DEM
{
    class DEM_timestamp_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(DEM_timestamp_ut);
        CPPUNIT_TEST(test_seconds);
        CPPUNIT_TEST(test_milliseconds);
        CPPUNIT_TEST(test_get_time);
        CPPUNIT_TEST(test_relational_operators);
        CPPUNIT_TEST(test_nanoseconds);
        CPPUNIT_TEST_SUITE_END();

        public:
        void setUp();
        void tearDown();

        protected:
        void test_seconds();
        void test_milliseconds();
        void test_get_time();
        void test_relational_operators();
        void test_nanoseconds();

        private:
        DEM_timestamp* ts;
        uint8_t* byte;

    };

    CPPUNIT_TEST_SUITE_REGISTRATION(DEM_timestamp_ut);

} // namespace

#endif // __DEM_DEM_TIMESTAMP_UT_H__
