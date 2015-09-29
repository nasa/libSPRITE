#ifndef __NET_UDP_UT_H__
#define __NET_UDP_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace net {
    class UDP_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(UDP_ut);

        CPPUNIT_TEST(test);
        CPPUNIT_TEST(test2);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void test();
        void test2();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(UDP_ut);

} // namespace

#endif // __NET_UDP_UT_H__
