#ifndef __NET_UDP_SERVER_UT_H__
#define __NET_UDP_SERVER_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace net {
    class UDP_server_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(UDP_server_ut);

        /**
         * @verifies{net-1.1}
         */
        CPPUNIT_TEST(test_server_create);
        CPPUNIT_TEST(spawn_echo);

        /**
         * @verifies{net-1.4}
         * @verifies{net-1.5}
         */
        CPPUNIT_TEST(test_server_echo);
        CPPUNIT_TEST(kill_echo);
        CPPUNIT_TEST(test_server_delete);

        /**
         * @verifies{net-1.1}
         */
        CPPUNIT_TEST(test_server_recreate);

        CPPUNIT_TEST_SUITE_END();

      public:
        void setUp();
        void tearDown();

      protected:
        void spawn_echo();
        void kill_echo();
        void test_server_create();
        void test_server_delete();
        void test_server_echo();
        void test_server_recreate();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(UDP_server_ut);

} // namespace

#endif // __NET_UDP_SERVER_UT_H__
