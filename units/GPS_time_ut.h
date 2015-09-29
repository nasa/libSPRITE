#ifndef __UNITS_GPS_TIME_UT_H__
#define __UNITS_GPS_TIME_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace units {
    class GPS_time_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(GPS_time_ut);

        /**
         * @verifies{units-4.1}
         * @verifies{units-4.2}
         * @verifies{units-4.3}
         * @verifies{units-4.4}
         * @verifies{units-4.5}
         * @verifies{units-4.6}
         */
        CPPUNIT_TEST(test);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(GPS_time_ut);

} // namespace

#endif // __UNITS_GPS_TIME_UT_H__
