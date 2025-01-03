#include "gfx.h"
#include "__macros.h"

#ifdef TARGET_PC
#include <strings.h>
#include <stdio.h>
#endif

u8 bgBuffer[SCREEN_HEIGHT * SCREEN_WIDTH * 4];

void Gfx_Init(){
    memset(bgBuffer, 1, sizeof(bgBuffer));

    #ifdef DEBUG
    #ifdef TARGET_PC
    {
        char buf[40];

        snprintf(buf, ARRAY_COUNT(buf), "Clearing bgBuffer, size : %d\n", sizeof(bgBuffer));

        puts(buf);
    }
    #endif
    #endif
}

