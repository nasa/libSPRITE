#ifndef __BASE_ASSERTION_H__
#define __BASE_ASSERTION_H__

#include <assert.h>

/**
 * Override the definition of assert. This is useful for unit testing.
 */
#ifdef ASSERT_THROWS_EXCEPTION
#undef assert
#define assert(x)                                                              \
    do {                                                                       \
        if(!(x))                                                               \
            throw - 1;                                                         \
    } while(0)
#endif

/**
 * Create a compile time assertion.
 * @note This must be used in a function. There are alternatives that use
 * typedefs for C++ templates to avoid that precondition.
 */
#define ct_assert(pred)                                                        \
    switch(0) {                                                                \
    case 0:                                                                    \
    case pred:                                                                 \
        ;                                                                      \
    }

#endif // __BASE_ASSERTION_H__
