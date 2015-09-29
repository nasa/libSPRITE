#ifndef __NET_UDP_CLIENT_H__
#define __NET_UDP_CLIENT_H__

#include "net/UDP_connection.h"

namespace net {
    class UDP_client : public UDP_connection {
      public:
        /**
         * Create a UDP client.
         * @satisfies{net-1.2}
         * @satisfies{net-1.3}
         */
        UDP_client(const char *host, int port);
    };
}

#endif //__NET_UDP_CLIENT_H__
