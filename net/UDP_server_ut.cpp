#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <base/XPRINTF.h>

#include "net/UDP_server.h"
#include "net/UDP_server_ut.h"

namespace net {

    namespace {
        const int PORT = 7500;
        const int BUFF_SIZE = 128;
        UDP_server *server;
        pid_t echo_pid;
    }

    void UDP_server_ut::setUp()
    {
    }

    void UDP_server_ut::tearDown()
    {
    }

    void UDP_server_ut::test_server_create()
    {
        /* Create a UDP server and make sure it's valid.
         */
        server = new UDP_server(PORT);
        CPPUNIT_ASSERT(server->is_valid());
    }

    void UDP_server_ut::test_server_delete()
    {
        delete server;
    }

    void UDP_server_ut::spawn_echo()
    {
        echo_pid = fork();
        if(0 == echo_pid) {
            execlp("udpecho.py", "udpecho.py", "-c", "localhost", "7500",
                   (char *)NULL);
        } else {
            sleep(1);
        }
    }

    void UDP_server_ut::kill_echo()
    {
        kill(echo_pid, 9);
        sleep(1);
    }

    void UDP_server_ut::test_server_echo()
    {
        /* Send a message and look for an echo return.
         */
        char sbuffer[] = "Hello world\n";
        int nsend = strlen(sbuffer);
        CPPUNIT_ASSERT_EQUAL(nsend, server->write(sbuffer, nsend));

        char rbuffer[BUFF_SIZE];
        int n = server->read(rbuffer, BUFF_SIZE);
        rbuffer[n] = '\0';
        CPPUNIT_ASSERT(0 == strcmp(rbuffer, sbuffer));
    }

    void UDP_server_ut::test_server_recreate()
    {
        /* Create a UDP server right after we destroyed the first and make sure
         * it's valid.
         */
        UDP_server server(PORT);
        CPPUNIT_ASSERT(server.is_valid());
    }
} // namespace
