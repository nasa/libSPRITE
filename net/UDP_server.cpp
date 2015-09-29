#include <arpa/inet.h>
#include <sys/socket.h>
#include <base/XPRINTF.h>

#include "net/UDP_server.h"

namespace net {
    UDP_server::UDP_server(int port) : UDP_connection(port)
    {
        /* Base class failed so abort.
         */
        if(!m_valid) {
            return;
        }

        if(bind(m_fd, (struct sockaddr *)(&m_addr), sizeof(m_addr))) {
            PERROR("bind");
            m_valid = false;
            return;
        }

        m_valid = true;
    }
}
