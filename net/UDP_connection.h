#ifndef __NET_UDP_CONNECTION_H__
#define __NET_UDP_CONNECTION_H__

#include <netinet/in.h>
#include "net/Socket.h"

namespace net
{
    class UDP_connection : public Socket
    {
      public:
        /**
         * Create a UDP connection class.
         * @param port UDP port.
         */
        UDP_connection(int port);

        /**
         * Create a UDP connection class.
         * @parm hostname Name or IP address of the host server.
         * @param port UDP port.
         */
        UDP_connection(const char *hostname, int port);

        /**
         * Read from a port.
         * @param buffer Buffer to read data into.
         * @param nbytes Size of the buffer.
         * @return Number of bytes read or -1 on error.
         */
        int read(void *buffer, unsigned int nbytes);

        /**
         * Write to a port.
         * @param buffer Data to write.
         * @param nbytes Number of bytes to write.
         * @return Number of bytes written or -1 on error.
         */
        int write(void *buffer, unsigned int nbytes);

      protected:
        /**
         * Unix socket structure.
         */
        struct sockaddr_in m_addr;
    };
}

#endif //__NET_UDP_CONNECTION_H__
