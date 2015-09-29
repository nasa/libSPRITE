#include "net/UDP_server.h"
#include "net/UDP_client.h"
#include "net/UDP_ut.h"

namespace net {

    void UDP_ut::setUp()
    {
    }

    void UDP_ut::tearDown()
    {
    }

    void UDP_ut::test()
    {
        const int port = 7500;

        UDP_server server(port);
        UDP_client client("localhost", port);
        CPPUNIT_ASSERT(true);
    }

    void UDP_ut::test2()
    {
        CPPUNIT_ASSERT(true);
    }

} // namespace
