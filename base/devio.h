#ifndef __BASE_DEVIO_H__
#define __BASE_DEVIO_H__

#include "base/byteswap.h"

#ifdef __cplusplus
extern "C" {
#endif

#define pciread8(x) devread8(x)
#define pciwrite8(x, y) devwrite8(x, y)
#define vmeread8(x) devread8(x)
#define vmewrite8(x, y) devwrite8(x, y)
#ifdef __BIG_ENDIAN__
#define pciread16(x) devread_s16(x)
#define pciread32(x) devread_s32(x)
#define pciread64(x) devread_s64(x)
#define pciwrite16(x, y) devwrite_s16(x, y)
#define pciwrite32(x, y) devwrite_s32(x, y)
#define pciwrite64(x, y) devwrite_s64(x, y)
#define vmeread16(x) devread16(x)
#define vmeread32(x) devread32(x)
#define vmeread64(x) devread64(x)
#define vmewrite16(x, y) devwrite16(x, y)
#define vmewrite32(x, y) devwrite32(x, y)
#define vmewrite64(x, y) devwrite64(x, y)
#else
#define pciread16(x) devread16(x)
#define pciread32(x) devread32(x)
#define pciread64(x) devread64(x)
#define pciwrite16(x, y) devwrite16(x, y)
#define pciwrite32(x, y) devwrite32(x, y)
#define pciwrite64(x, y) devwrite64(x, y)
#define vmeread16(x) devread_s16(x)
#define vmeread32(x) devread_s32(x)
#define vmeread64(x) devread_s64(x)
#define vmewrite16(x, y) devwrite_s16(x, y)
#define vmewrite32(x, y) devwrite_s32(x, y)
#define vmewrite64(x, y) devwrite_s64(x, y)
#endif

typedef char *addr_t;

/**
 Read an 8 bit-value.
 */
static __inline__ uint8_t devread8(const addr_t in_port)
{
    return *(volatile uint8_t *)(in_port);
}

/**
 Read a 16 bit-value.
 */
static __inline__ uint16_t devread16(const addr_t in_port)
{
    return *(volatile uint16_t *)(in_port);
}

/**
 Read a 32 bit-value.
 */
static __inline__ uint32_t devread32(const addr_t in_port)
{
    return *(volatile uint32_t *)(in_port);
}

/**
 Read a 64 bit-value.
 */
static __inline__ uint64_t devread64(const addr_t in_port)
{
    return *(volatile uint64_t *)(in_port);
}

/**
 Write an 8 bit-value.
 */
static __inline__ void devwrite8(const addr_t in_port, const uint8_t in_value)
{
    *(volatile uint8_t *)(in_port) = in_value;
}

/**
 Write a 16 bit-value.
 */
static __inline__ void devwrite16(const addr_t in_port, const uint16_t in_value)
{
    *(volatile uint16_t *)(in_port) = in_value;
}

/**
 Write a 32 bit-value.
 */
static __inline__ void devwrite32(const addr_t in_port, const uint32_t in_value)
{
    *(volatile uint32_t *)(in_port) = in_value;
}

/**
 Write a 64 bit-value.
 */
static __inline__ void devwrite64(const addr_t in_port, const uint64_t in_value)
{
    *(volatile uint64_t *)(in_port) = in_value;
}

/**
 Read a 16 bit-value with byte-swap.
 */
static __inline__ uint16_t devread_s16(const addr_t in_port)
{
    return byteswap16(*(volatile uint16_t *)(in_port));
}

/**
 Read a 32 bit-value with byte-swap.
 */
static __inline__ uint32_t devread_s32(const addr_t in_port)
{
    return byteswap32(*(volatile uint32_t *)(in_port));
}

/**
 Read a 64 bit-value with byte-swap.
 */
static __inline__ uint64_t devread_s64(const addr_t in_port)
{
    return byteswap64(*(volatile uint64_t *)(in_port));
}

/**
 Write a 16 bit-value with byte-swap.
 */
static __inline__ void devwrite_s16(const addr_t in_port, uint16_t in_value)
{
    *(volatile uint16_t *)(in_port) = byteswap16(in_value);
}

/**
 Write a 32 bit-value with byte-swap.
 */
static __inline__ void devwrite_s32(const addr_t in_port, uint32_t in_value)
{
    *(volatile uint32_t *)(in_port) = byteswap32(in_value);
}

/**
 Write a 64 bit-value with byte-swap.
 */
static __inline__ void devwrite_s64(const addr_t in_port, uint64_t in_value)
{
    *(volatile uint64_t *)(in_port) = byteswap64(in_value);
}

#ifdef __cplusplus
}
#endif
#endif /* __BASE_DEVIO_H__ */
