#include <netdb.h>
#include <arpa/inet.h>
#include <base/XPRINTF.h>

#include "net/UDP_connection.h"

namespace net {

    static bool set_reuse(int fd)
    {
        /* Make the address we're going to bind resuable so we do not have to
         * wait for the linger time to expire before being able to create a new
         * socket on the same address after the socket is closed.
         */
        int one = 1;
        if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *)&one,
                      sizeof(one))) {
            PERROR("setsockopt");
            return false;
        }

        return true;
    }

    UDP_connection::UDP_connection(int port)
        : Socket(SOCK_DGRAM)
        , m_addr()
    {
        m_addr.sin_family = AF_INET;
        m_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        m_addr.sin_port = htons(port);

        m_valid = set_reuse(m_fd);
    }

    UDP_connection::UDP_connection(const char *hostname, int port)
        : Socket(SOCK_DGRAM)
        , m_addr()
    {
        /* TODO: gethostbyname is deprecated. Replace with getaddrinfo.
         */
        hostent *host;
        host = gethostbyname(hostname);
        if(NULL == host) {
            PERROR("gethostbyname");
            m_valid = false;
            return;
        }

        DPRINTF("Official name is %s\n", host->h_name);
        DPRINTF("IP address is %s\n",
                inet_ntoa(*(struct in_addr *)(host->h_addr_list[0])));

        m_addr.sin_port = htons(port);
        m_addr.sin_family = AF_INET;
        /* TODO: We are being lazy and taking the first address returned by
         * gethostbyname. In some cases, we may want to use a different
         * address.
         */
        memcpy(&m_addr.sin_addr.s_addr, host->h_addr, host->h_length);

        m_valid = set_reuse(m_fd);
    }

    UDP_connection::~UDP_connection()
    {
    }

    int UDP_connection::read(void *buffer, unsigned int nbytes)
    {
        static socklen_t addr_len = sizeof(m_addr);
        int rval;

        rval = recvfrom(m_fd, buffer, nbytes, 0, (struct sockaddr *)(&m_addr),
                        &addr_len);
        if(-1 == rval) {
            PERROR("recvfrom");
        }

        return rval;
    }

    int UDP_connection::read(void *buffer, unsigned int nbytes,
                             units::Nanoseconds timeout)
    {
        /* Set timeout.
         */
        struct timeval tv;
        tv.tv_sec = timeout / units::SEC;
        tv.tv_usec = (timeout % units::SEC) / units::USEC;

        /* Use select to see if data is ready to be read within the timeout
         * period.
         */
        fd_set m_readfds;
        FD_ZERO(&m_readfds);
        FD_SET(m_fd, &m_readfds);
        if(-1 == select(m_fd + 1, &m_readfds, NULL, NULL, &tv)) {
            PERROR("select");
            return -1;
        }

        /* If there is data to read, read it, else, return 0.
         */
        return (FD_ISSET(m_fd, &m_readfds)) ? read(buffer, nbytes) : 0;
    }

    int UDP_connection::write(const void *buffer, unsigned int nbytes)
    {
        int rval;

        rval = sendto(m_fd, buffer, nbytes, 0, (struct sockaddr *)(&m_addr),
                      sizeof(m_addr));
        if(-1 == rval) {
            PERROR("sendto");
        }

        return rval;
    }
}
