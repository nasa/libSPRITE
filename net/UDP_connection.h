#ifndef __NET_UDP_CONNECTION_H__
#define __NET_UDP_CONNECTION_H__

#include <netinet/in.h>

#include "net/Socket.h"
#include "units/Nanoseconds.h"

namespace net {
    class UDP_connection : public Socket {
      public:
        /**
         * Create a UDP connection class.
         * @param port UDP port.
         */
        UDP_connection(int port);

        /**
         * Destructor.
         */
        virtual ~UDP_connection();

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
         * @satisfies{net-1.4}
         */
        int read(void *buffer, unsigned int nbytes);

        /**
         * Read from a port with timeout
         * @param buffer Buffer to read data into.
         * @param nbytes Size of the buffer.
         * @oaram timeout Timeout. 0 means poll.
         * @return Number of bytes read or -1 on error.
         * @satisfies{net-1.6}
         */
        int read(void *buffer, unsigned int nbytes, units::Nanoseconds timeout);

        /**
         * Write to a port.
         * @param buffer Data to write.
         * @param nbytes Number of bytes to write.
         * @return Number of bytes written or -1 on error.
         * @satisfies{net-1.5}
         */
        int write(const void *buffer, unsigned int nbytes);

      protected:
        /**
         * Unix socket structure.
         */
        struct sockaddr_in m_addr;
    };
}

#endif //__NET_UDP_CONNECTION_H__
