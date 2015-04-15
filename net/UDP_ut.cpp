#include "net/UDP_server.h"
#include "net/UDP_client.h"
#include "net/UDP_ut.h"

namespace net
{

    void UDP_ut::setUp()
    {
        fprintf(stderr, "setup\n");
    }

    void UDP_ut::tearDown()
    {
        fprintf(stderr, "teardown\n");
    }

    void UDP_ut::test()
    {
        const int port = 7500;

        UDP_server server(port);
        //UDP_client client("localhost", port);
        UDP_client client("127.0.0.1", port);
        CPPUNIT_ASSERT(true);
    }

    void UDP_ut::test2()
    {
        CPPUNIT_ASSERT(true);
    }

} // namespace
