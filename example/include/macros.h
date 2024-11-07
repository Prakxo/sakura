#ifndef MACROS_H
#define MACROS_H

#include "selftypes.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))

#define ASSERT(expr)                                \
    (                                               \
                                                    \
        {                                           \
            char buf[50];                           \
            if ((expr) == TRUE) {                   \
                sprintf(buf, "%s failed!", #expr); \
                puts(buf);                          \
            }                                       \
        } \
    )

#endif