/******************************************************************************
 * Copyright (c) 2012 - Daniel L. Heater
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *****************************************************************************/

#include <stdlib.h>
#include "SRTX/Buffer.h"


namespace SRTX
{

    Buffer::Buffer(unsigned int nbytes) :
        m_nbytes(nbytes),
        m_read_abort(false),
        m_update_count(0)
    {
    }


    void Buffer::abort_read()
    {
        m_sync.lock();
        m_read_abort = true;
        m_sync.release();
        m_sync.unlock();
    }


    bool copy_entry(Buffer& dest, Buffer& src, unsigned int nbytes)
    {
        uint8_t tmp[nbytes];

        return src.read(tmp, nbytes) && dest.write(tmp, nbytes);
    }

} // namespace
