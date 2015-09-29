#ifndef __BASE_BYTESWAP__
#define __BASE_BYTESWAP__

#include "base/types.h"
#include <string.h>

enum ByteOrder {
    LittleEndian,
    BigEndian
};

#define byteswap16(x)                                                          \
    (uint16_t)((((uint16_t)(x) & 0xff00) >> 8) |                               \
               (((uint16_t)(x) & 0x00ff) << 8))
#define byteswap32(x)                                                          \
    (uint32_t)((((uint32_t)(x) & 0xff000000) >> 24) |                          \
               (((uint32_t)(x) & 0x00ff0000) >> 8) |                           \
               (((uint32_t)(x) & 0x0000ff00) << 8) |                           \
               (((uint32_t)(x) & 0x000000ff) << 24))

static __inline__ uint64_t byteswap64(uint64_t x)
{
    uint32_t b = (x << 32) >> 32;
    uint32_t t = x >> 32;

    return ((uint64_t)byteswap32(b) << 32) | byteswap32(t);
}

static __inline__ int isbigendian()
{
    union endian_test_u {
        unsigned char bytes[2];
        uint16_t value;
    };
    static endian_test_u endian_test;
    endian_test.bytes[0] = 1;
    endian_test.bytes[1] = 0;

    return 1 != endian_test.value;
}

#endif /* __BASE_BYTESWAP__ */
