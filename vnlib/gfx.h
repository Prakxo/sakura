#ifndef VNLIB_GFX_H
#define VNLIB_GFX_H

#include "__selftypes.h"

#ifdef TARGET_PC
#include "gfx_pc.h"
#endif

extern u8 bgBuffer[];

extern void Gfx_Init(void);

#endif