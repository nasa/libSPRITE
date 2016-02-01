#include <stdlib.h>
#include "SRTX/Buffer.h"
#include "base/XPRINTF.h"

namespace SRTX {

    Buffer::Buffer(unsigned int nbytes)
        : m_nbytes(nbytes)
        , m_valid(false)
        , m_sync()
        , m_update_count(0)
    {
    }

    Buffer::~Buffer()
    {
        m_valid = false;
        abort_read();
    }

    void Buffer::abort_read()
    {
        if(false == m_sync.lock()) {
            EPRINTF("Error obtaining lock\n");
            return;
        }

        m_sync.abort_wait();

        if(false == m_sync.unlock()) {
            EPRINTF("Error releasing lock\n");
            return;
        }
    }

    bool copy_entry(Buffer &dest, Buffer &src, unsigned int nbytes)
    {
        uint8_t tmp[nbytes];
        return src.read(tmp, nbytes) && dest.write(tmp, nbytes);
    }

} // namespace
