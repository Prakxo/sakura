#ifndef MACROS_H
#define MACROS_H

#include "selftypes.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#ifdef DEBUG
#define ASSERT(expr)                                \
    (                                               \
                                                    \
        {                                           \
            char buf[150];                           \
            if ((expr) == TRUE) {                   \
                sprintf(buf, "%s failed! in %s @ %s-%d", #expr, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
                puts(buf);                          \
                exit(EXIT_FAILURE);                 \
            }                                       \
        })
#else
#define ASSERT(expr)
#endif

#endif