#ifndef __NET_UDP_SERVER_H__
#define __NET_UDP_SERVER_H__

#include "net/UDP_connection.h"

namespace net {
    class UDP_server : public UDP_connection {
      public:
        /**
         * Create a UDP server.
         * @satisfies{net-1.1}
         */
        UDP_server(int port);
    };
}

#endif //__NET_UDP_SERVER_H__
