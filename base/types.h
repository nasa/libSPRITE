#ifndef __BASE_TYPES__
#define __BASE_TYPES__

#ifdef __VXWORKS__
#include <types/vxTypes.h>
#else                        // Assume POSIX compliant OS
#define __STDC_FORMAT_MACROS // Allow for PRId64 for printing 64-bit integers.
#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>
#endif

#ifndef NEAR_ZERO
#define NEAR_ZERO 1e-16
#endif

#endif /* __BASE_TYPES__ */
