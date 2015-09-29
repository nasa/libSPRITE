#include <arpa/inet.h>
#include <sys/socket.h>
#include <base/XPRINTF.h>

#include "net/UDP_client.h"

namespace net {
    UDP_client::UDP_client(const char *hostname, int port)
        : UDP_connection(hostname, port)
    {
    }
}
