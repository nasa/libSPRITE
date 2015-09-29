#ifndef __NET_UDP_CLIENT_UT_H__
#define __NET_UDP_CLIENT_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace net {
    class UDP_client_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(UDP_client_ut);

        CPPUNIT_TEST(spawn_echo);

        /**
         * @verifies{net-1.2}
         * @verifies{net-1.4}
         * @verifies{net-1.5}
         */
        CPPUNIT_TEST(test_client);

        /**
         * @verifies{net-1.2}
         * @verifies{net-1.4}
         * @verifies{net-1.5}
         * @verifies{net-1.6}
         */
        CPPUNIT_TEST(test_read_timeout);

        /**
         * @verifies{net-1.3}
         * @verifies{net-1.4}
         * @verifies{net-1.5}
         */
        CPPUNIT_TEST(test_client_ip);
        CPPUNIT_TEST(kill_echo);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void spawn_echo();
        void kill_echo();
        void test_client();
        void test_read_timeout();
        void test_client_ip();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(UDP_client_ut);

} // namespace

#endif // __NET_UDP_CLIENT_UT_H__
