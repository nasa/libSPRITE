#ifndef __UTIL_SERIAL_BUFFER_UT_H__
#define __UTIL_SERIAL_BUFFER_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace util {

    class Serial_buffer_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Serial_buffer_ut);

        /**
         * @verifies{util-3.1}
         */
        CPPUNIT_TEST(test_serdes);

        CPPUNIT_TEST_SUITE_END();

      public:
        Serial_buffer_ut();

        void setUp();
        void tearDown();

      protected:
        void test_serdes();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Serial_buffer_ut);

} // namespace

#endif // __UTIL_SERIAL_BUFFER_UT_H__
