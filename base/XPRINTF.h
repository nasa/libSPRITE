/*
===============================================================================
                        COPYRIGHT NOTICE

Copyright (C) 2001-2014 Daniel L. Heater
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

#ifndef __BASE_XPRINTF_H__
#define __BASE_XPRINTF_H__

#include <stdio.h>
#include <string.h>

#ifdef XPRINT_LOCATION
#define LPRINTF(type) do { \
        fprintf(stderr, "%s:%s:%d:",(type), __FILE__, __LINE__); \
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
#define EPRINTF(x...) do { \
    LPRINTF("ERROR"); \
    fprintf(stderr, x); \
} while(0)
#define PERROR(x...) do { \
        LPRINTF("ERROR"); perror(x); \
} while(0)
#define PERRORNO(err, x...) do { \
    EPRINTF(x); \
    fprintf(stderr, ": %s\n", strerror(err)); \
} while(0)
#endif

/* Clear the NO_PRINT_ERROR flag for the next inclusion. */
#undef NO_PRINT_ERROR

#undef WPRINTF
#ifdef NO_PRINT_WARNING
#define WPRINTF(x...)
#else
#define WPRINTF(x...) do { \
    LPRINTF("WARNING"); \
    fprintf(stderr, x); \
} while(0)
#endif

/* Clear the NO_PRINT_WARN flag for the next inclusion. */
#undef NO_PRINT_WARNING

#undef IPRINTF
#ifdef NO_PRINT_INFO
#define IPRINTF(x...)
#else
#define IPRINTF(x...) do { \
    printf(x); \
} while(0)
#endif

/* Clear the NO_PRINT_INFO flag for the next inclusion. */
#undef NO_PRINT_INFO

#undef DPRINTF
#ifdef PRINT_DEBUG
#define DPRINTF(x...) do { \
    LPRINTF("DEBUG"); \
    fprintf(stderr, x); \
} while(0)
#else
#define DPRINTF(x...)
#endif

/* Clear the PRINT_DEBUG flag for the next inclusion. */
#undef PRINT_DEBUG

#endif /* __BASE_XPRINTF_H__ */
