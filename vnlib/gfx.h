#ifndef VNLIB_GFX_H
#define VNLIB_GFX_H

#include "__macros.h"
#include "__selftypes.h"

#ifdef TARGET_PC
#include "gfx_pc.h"
#endif

extern u8 bgBuffer[SCREEN_HEIGHT * SCREEN_WIDTH * 4];

extern void Gfx_Init(void);

#endif
