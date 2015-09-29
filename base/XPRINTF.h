#ifndef __BASE_XPRINTF_H__
#define __BASE_XPRINTF_H__

#include <stdio.h>
#include <string.h>

#ifdef XPRINT_LOCATION
#define LPRINTF(type)                                                          \
    do {                                                                       \
        fprintf(stderr, "%s:%s:%d:", (type), __FILE__, __LINE__);              \
    } while(0)
#else
#define LPRINTF(type)
#endif
#undef XPRINT_LOCATION

#undef EPRINTF
#ifdef NO_PRINT_ERROR
#define EPRINTF(x...)
#define PERROR(x...)
#define PERRORNO(x...)
#else
#define EPRINTF(x...)                                                          \
    do {                                                                       \
        LPRINTF("ERROR");                                                      \
        fprintf(stderr, x);                                                    \
    } while(0)
#define PERROR(x...)                                                           \
    do {                                                                       \
        LPRINTF("ERROR");                                                      \
        perror(x);                                                             \
    } while(0)
#define PERRORNO(err, x...)                                                    \
    do {                                                                       \
        EPRINTF(x);                                                            \
        fprintf(stderr, ": %s\n", strerror(err));                              \
    } while(0)
#endif

/* Clear the NO_PRINT_ERROR flag for the next inclusion. */
#undef NO_PRINT_ERROR

#undef WPRINTF
#ifdef NO_PRINT_WARNING
#define WPRINTF(x...)
#else
#define WPRINTF(x...)                                                          \
    do {                                                                       \
        LPRINTF("WARNING");                                                    \
        fprintf(stderr, x);                                                    \
    } while(0)
#endif

/* Clear the NO_PRINT_WARN flag for the next inclusion. */
#undef NO_PRINT_WARNING

#undef IPRINTF
#ifdef NO_PRINT_INFO
#define IPRINTF(x...)
#else
#define IPRINTF(x...)                                                          \
    do {                                                                       \
        printf(x);                                                             \
    } while(0)
#endif

/* Clear the NO_PRINT_INFO flag for the next inclusion. */
#undef NO_PRINT_INFO

#undef DPRINTF
#ifdef PRINT_DEBUG
#define DPRINTF(x...)                                                          \
    do {                                                                       \
        LPRINTF("DEBUG");                                                      \
        fprintf(stderr, x);                                                    \
    } while(0)
#else
#define DPRINTF(x...)
#endif

/* Clear the PRINT_DEBUG flag for the next inclusion. */
#undef PRINT_DEBUG

#endif /* __BASE_XPRINTF_H__ */
