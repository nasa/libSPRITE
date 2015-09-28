#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <base/XPRINTF.h>

#include "net/UDP_client.h"
#include "net/UDP_client_ut.h"

namespace net {
    namespace {
        const int PORT = 7500;
        const unsigned int BUFF_SIZE = 128;
        pid_t echo_pid;
    }

    void UDP_client_ut::setUp()
    {
    }

    void UDP_client_ut::tearDown()
    {
    }

    void UDP_client_ut::spawn_echo()
    {
        echo_pid = fork();
        if(0 == echo_pid) {
            execlp("udpecho.py", "udpecho.py", "-s", "7500", (char *)NULL);
        } else {
            sleep(1);
        }
    }

    void UDP_client_ut::kill_echo()
    {
        kill(echo_pid, 9);
        sleep(1);
    }

    void UDP_client_ut::test_client()
    {
        UDP_client client("localhost", PORT);

        /* Send a message and look for an echo return.
         */
        char sbuffer[] = "Hello world\n";
        int nsend = strlen(sbuffer);
        CPPUNIT_ASSERT_EQUAL(nsend, client.write(sbuffer, nsend));

        char rbuffer[BUFF_SIZE];
        int n = client.read(rbuffer, BUFF_SIZE);
        rbuffer[n] = '\0';
        CPPUNIT_ASSERT(0 == strcmp(rbuffer, sbuffer));
    }

    void UDP_client_ut::test_read_timeout()
    {
        UDP_client client("localhost", PORT);
        units::Nanoseconds timeout(units::Nanoseconds(units::USEC * 10));

        char rbuffer[BUFF_SIZE];
        CPPUNIT_ASSERT_EQUAL(0, client.read(rbuffer, BUFF_SIZE, timeout));

        timeout = units::Nanoseconds(0);
        CPPUNIT_ASSERT_EQUAL(0, client.read(rbuffer, BUFF_SIZE, timeout));

        /* Send a message and look for an echo return.
         */
        char sbuffer[] = "Hello world\n";
        int nsend = strlen(sbuffer);
        CPPUNIT_ASSERT_EQUAL(nsend, client.write(sbuffer, nsend));

        int n = client.read(rbuffer, BUFF_SIZE);
        rbuffer[n] = '\0';
        CPPUNIT_ASSERT(0 == strcmp(rbuffer, sbuffer));
    }

    void UDP_client_ut::test_client_ip()
    {
        UDP_client client("127.0.0.1", PORT);

        /* Send a message and look for an echo return.
         */
        char sbuffer[] = "Hello world\n";
        int nsend = strlen(sbuffer);
        CPPUNIT_ASSERT_EQUAL(nsend, client.write(sbuffer, nsend));

        char rbuffer[BUFF_SIZE];
        int n = client.read(rbuffer, BUFF_SIZE);
        rbuffer[n] = '\0';
        CPPUNIT_ASSERT(0 == strcmp(rbuffer, sbuffer));
    }
} // namespace
