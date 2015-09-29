#ifndef __SRTX_MESSAGE_UT_H__
#define __SRTX_MESSAGE_UT_H__

#include <cppunit/extensions/HelperMacros.h>

namespace SRTX {

    /**
     * A set of test for sending messages through a publish/subscribe system.
     */
    class Message_ut : public CppUnit::TestFixture {

        CPPUNIT_TEST_SUITE(Message_ut);

        CPPUNIT_TEST(test_Message);
        CPPUNIT_TEST(test_pub_sub);
        CPPUNIT_TEST(test_async);

        CPPUNIT_TEST_SUITE_END();

      public:
        Message_ut();
        ~Message_ut();
        void setUp();
        void tearDown();

      protected:
        void test_Message();

        /**
         * Test sending messages between a publisher and a subscriber running at
         * the same rate.
         */
        void test_pub_sub();
        void test_async();
    };

    CPPUNIT_TEST_SUITE_REGISTRATION(Message_ut);

} // namespace

#endif // __SRTX_MESSAGE_UT_H__
