/*
===============================================================================
                        COPYRIGHT NOTICE

Copyright (C) 2004-2014 Daniel L. Heater
International Copyright Secured.  All Rights Reserved.

-------------------------------------------------------------------------------

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

o Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
o Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
o The authors name may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

===============================================================================
*/

#ifndef __BASE_BYTESWAP__
#define __BASE_BYTESWAP__

#include "base/types.h"
#include <string.h>

#define byteswap16(x)  ( \
        (((uint16_t)(x) & 0xff00) >> 8) | \
        (((uint16_t)(x) & 0x00ff) << 8))
#define byteswap32(x)  ( \
        (((uint32_t)(x) & 0xff000000) >> 24) | \
        (((uint32_t)(x) & 0x00ff0000) >> 8) | \
        (((uint32_t)(x) & 0x0000ff00) << 8) | \
        (((uint32_t)(x) & 0x000000ff) << 24))

static __inline__ uint64_t byteswap64( uint64_t x )
{
    uint32_t b = ( x << 32 ) >> 32;
    uint32_t t = x >> 32;

    return ( ( uint64_t ) byteswap32( b ) << 32 ) | byteswap32( t );
}

static __inline__ int isbigendian()
{
#ifdef USED_TO_WORK
    static unsigned char endian_test[ 2 ] = { 1, 0 };
    return 1 != *( uint16_t* ) endian_test;
#else
    union endian_test_u {
        unsigned char bytes[2];
        uint16_t value;
    };
    static endian_test_u endian_test;
    endian_test.bytes[0] = 1;
    endian_test.bytes[1] = 0;

    return 1 != endian_test.value;
#endif
}

#endif /* __BASE_BYTESWAP__ */
