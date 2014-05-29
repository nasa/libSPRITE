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

static __inline__ double byteswapDouble( double x )
{
      char* swap_val = (char*)&x;
      char temp = 0;
      int i = 0;
      int j = sizeof(double)-1;
      while (i<j)
      {
         temp = swap_val[i];
         swap_val[i] = swap_val[j];
         swap_val[j] = temp;
         i++, j--;
      }

      memcpy(&x, swap_val, sizeof(double));
      return(x);
}

#endif /* __BASE_BYTESWAP__ */
