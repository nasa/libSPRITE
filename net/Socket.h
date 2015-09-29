#ifndef __NET_SOCKET_H__
#define __NET_SOCKET_H__

#include <sys/socket.h>
#include "net/Socket.h"

namespace net {
    class Socket {
      public:
        /**
         * Is the socket valid?
         * @return true if valid, else false.
         */
        bool is_valid() const
        {
            return m_valid;
        }

      protected:
        /**
         * Create a socket
         * @param type Socket type.
         */
        Socket(int type);

        /**
         * Destructor.
         */
        virtual ~Socket();

        /**
         * Class valid?
         */
        bool m_valid;

        /**
         * Socket descriptor
         */
        int m_fd;
    };
}
#endif //__NET_SOCKET_H__
