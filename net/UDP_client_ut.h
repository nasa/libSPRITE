#ifndef __NET_UDP_CLIENT_UT_H__
#define __NET_UDP_CLIENT_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace net
{
    class UDP_client_ut : public CppUnit::TestFixture
    {

        CPPUNIT_TEST_SUITE(UDP_client_ut);

        CPPUNIT_TEST(spawn_echo);
        CPPUNIT_TEST(test_client);
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
        void test_client_ip();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(UDP_client_ut);

} // namespace

#endif // __NET_UDP_CLIENT_UT_H__
