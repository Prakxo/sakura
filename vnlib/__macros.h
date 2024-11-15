#ifndef __MACROS_H
#define __MACROS_H

#include "__selftypes.h"

#define ARRAY_COUNT(arr) (s32)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (u32)(sizeof(arr) / sizeof(arr[0]))


#define ASSERT(expr)                                \
    (                                               \
                                                    \
        {                                           \
            char buf[100];                           \
            if ((expr) == TRUE) {                   \
                sprintf(buf, "%s failed! in %s @ %s-%d\n", #expr, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
                puts(buf);                          \
            }                                       \
        })

#endif