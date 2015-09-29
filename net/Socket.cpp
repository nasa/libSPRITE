#include <unistd.h>
#include "net/Socket.h"
#include "base/XPRINTF.h"

namespace net {

    Socket::Socket(int type)
        : m_valid(false)
        , m_fd(-1)
    {
        m_fd = socket(PF_INET, type, 0);
        if(-1 == m_fd) {
            PERROR("socket");
            return;
        }

        m_valid = true;
    }

    Socket::~Socket()
    {
        (void)close(m_fd);
        m_fd = -1;
    }
}
